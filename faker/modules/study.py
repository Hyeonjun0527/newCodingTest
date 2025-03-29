from .common import get_connection, fake
import random

def insert_study_spaces(num_spaces=500):
    conn = get_connection()
    study_space_ids = []
    
    # 스터디 주제 예시
    study_subjects = [
        "Java 기초", "Spring 심화", "React 입문", "알고리즘 스터디", "CS 지식", 
        "코딩 테스트 대비", "디자인 패턴", "데이터베이스", "네트워크 기초", "보안 기초",
        "머신러닝 입문", "파이썬 데이터분석", "웹 개발 실습", "모바일 앱 개발", "클라우드 서비스",
        "DevOps 실무", "프로젝트 관리", "UI/UX 디자인", "블록체인 기초", "게임 개발 입문"
    ]
    
    try:
        with conn.cursor() as cursor:
            sql = """
                INSERT INTO study_space
                (scheduled_interview_time, subject, deleted, created_at, updated_at, personnel_count)
                VALUES (%s, %s, %s, %s, %s, %s)
            """
            
            for i in range(num_spaces):
                scheduled_interview_time = fake.future_datetime(end_date='+3m')
                subject = random.choice(study_subjects)
                deleted = 'FALSE'
                created_at = fake.date_time_between(start_date='-6m', end_date='-1d')
                updated_at = fake.date_time_between(start_date=created_at, end_date='now')
                personnel_count = random.randint(1, 10)
                
                cursor.execute(sql, (
                    scheduled_interview_time, subject, deleted, created_at, updated_at, personnel_count
                ))
                study_space_ids.append(cursor.lastrowid)
                
                if (i + 1) % 100 == 0:
                    conn.commit()
                    print(f"{i + 1}개 스터디 공간 데이터 삽입됨.")
            
            conn.commit()
            print(f"총 {len(study_space_ids)}개의 스터디 공간 데이터 삽입 완료!")
            
    finally:
        conn.close()
        
    return study_space_ids

def insert_daily_study_contents(member_ids, study_space_ids, num_contents=3000):
    conn = get_connection()
    daily_study_ids = []
    
    # 스터디 주제 예시 (study_space의 주제보다 더 상세한 주제)
    detailed_subjects = [
        "자바 컬렉션 프레임워크", "스프링 AOP 심화", "리액트 훅스 활용", "그리디 알고리즘 문제풀이", 
        "운영체제 메모리 관리", "SQL 최적화 기법", "자료구조 구현", "HTTP 프로토콜 분석",
        "파이썬 데이터 시각화", "클라우드 배포 자동화", "CI/CD 파이프라인 구축", "디자인 패턴 적용",
        "코틀린 문법 학습", "플러터 UI 구현", "머신러닝 모델 튜닝", "네트워크 보안 실습",
        "마이크로서비스 아키텍처", "도커 컨테이너화", "리액티브 프로그래밍", "함수형 프로그래밍"
    ]
    
    # 가능한 진행 상태
    progress_statuses = ['PENDING', 'IN_PROGRESS', 'COMPLETE', 'ABSENT']
    
    try:
        with conn.cursor() as cursor:
            sql = """
                INSERT INTO daily_study_content
                (member_id, study_space_id, description, created_at, updated_at, deleted, 
                progress_start_time, progress_status, plan_time, subject, link, is_private)
                VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s)
            """
            
            for i in range(num_contents):
                member_id = random.choice(member_ids)
                study_space_id = random.choice(study_space_ids)
                description = fake.paragraph(nb_sentences=2)[:250]
                created_at = fake.date_time_between(start_date='-3m', end_date='-1d')
                updated_at = fake.date_time_between(start_date=created_at, end_date='now')
                deleted = random.choices([True, False], weights=[0.1, 0.9])[0]  # 10%는 삭제됨
                
                progress_start_time = fake.date_time_between(start_date='-3m', end_date='+1m')
                progress_status = random.choice(progress_statuses)
                
                # 계획 시간은 시작 시간 이전 또는 이후로 설정
                if progress_status in ['PENDING', 'IN_PROGRESS']:
                    plan_time = fake.date_time_between(start_date=progress_start_time, end_date='+2m')
                else:
                    plan_time = fake.date_time_between(start_date='-3m', end_date=progress_start_time)
                
                subject = random.choice(detailed_subjects)
                
                # 약 70%는 링크 있음
                link = None
                if random.random() < 0.7:
                    link_types = ['zoom.us', 'meet.google.com', 'teams.microsoft.com', 'github.com']
                    link_domain = random.choice(link_types)
                    link = f"https://{link_domain}/{fake.uuid4()}"[:50]  # 최대 50자
                
                is_private = random.choices([True, False], weights=[0.2, 0.8])[0]  # 20%는 비공개
                
                cursor.execute(sql, (
                    member_id, study_space_id, description, created_at, updated_at, deleted,
                    progress_start_time, progress_status, plan_time, subject, link, is_private
                ))
                daily_study_ids.append(cursor.lastrowid)
                
                if (i + 1) % 500 == 0:
                    conn.commit()
                    print(f"{i + 1}개 일일 스터디 내용 데이터 삽입됨.")
            
            conn.commit()
            print(f"총 {len(daily_study_ids)}개의 일일 스터디 내용 데이터 삽입 완료!")
            
    finally:
        conn.close()
        
    return daily_study_ids

def insert_attendances(daily_study_ids, num_attendances=2500):
    conn = get_connection()
    
    # 가능한 출석 상태
    attendance_statuses = ['ATTENDANCE', 'LATE', 'ABSENCE']
    
    try:
        with conn.cursor() as cursor:
            sql = """
                INSERT INTO attendance
                (daily_study_id, status, created_at, updated_at)
                VALUES (%s, %s, %s, %s)
            """
            
            # 중복 방지를 위한 집합
            processed_daily_studies = set()
            count = 0
            
            while count < num_attendances and len(processed_daily_studies) < len(daily_study_ids):
                daily_study_id = random.choice(daily_study_ids)
                
                # 중복 체크 (한 스터디에 대해 하나의 출석 정보만 생성)
                if daily_study_id in processed_daily_studies:
                    continue
                
                processed_daily_studies.add(daily_study_id)
                
                # 스터디 내용의 진행 상태에 따라 출석 상태 결정
                # 일일 스터디의 progress_status 확인
                cursor.execute("""
                    SELECT progress_status FROM daily_study_content 
                    WHERE daily_study_id = %s
                """, (daily_study_id,))
                progress_status = cursor.fetchone()[0]
                
                if progress_status == 'ABSENT':
                    status = 'ABSENCE'
                elif progress_status == 'COMPLETE':
                    status = random.choices(['ATTENDANCE', 'LATE'], weights=[0.8, 0.2])[0]
                else:
                    status = random.choice(attendance_statuses)
                
                # 스터디 내용의 생성 시간 가져오기
                cursor.execute("""
                    SELECT created_at, progress_start_time FROM daily_study_content 
                    WHERE daily_study_id = %s
                """, (daily_study_id,))
                created_at_study, progress_start_time = cursor.fetchone()
                
                created_at = fake.date_time_between(start_date=created_at_study, end_date='+1d')
                updated_at = fake.date_time_between(start_date=created_at, end_date='+1d')
                
                cursor.execute(sql, (daily_study_id, status, created_at, updated_at))
                count += 1
                
                if count % 500 == 0:
                    conn.commit()
                    print(f"{count}개 출석 데이터 삽입됨.")
            
            conn.commit()
            print(f"총 {count}개의 출석 데이터 삽입 완료!")
            
    finally:
        conn.close()

def insert_dashboard_categories():
    conn = get_connection()
    dashboard_category_ids = {}
    
    # 상위 대시보드 카테고리
    parent_categories = [
        {"id": 100, "name": "학습 통계", "code": "LRN", "level": 1, "parent_id": None},
        {"id": 200, "name": "참여도 분석", "code": "PRT", "level": 1, "parent_id": None},
        {"id": 300, "name": "성장 지표", "code": "GRW", "level": 1, "parent_id": None},
        {"id": 400, "name": "활동 요약", "code": "ACT", "level": 1, "parent_id": None}
    ]
    
    # 하위 대시보드 카테고리
    child_categories = {
        100: [
            {"id": 101, "name": "학습 시간", "code": "LT1", "level": 2, "parent_id": 100},
            {"id": 102, "name": "학습 빈도", "code": "LF1", "level": 2, "parent_id": 100},
            {"id": 103, "name": "학습 주제", "code": "LS1", "level": 2, "parent_id": 100}
        ],
        200: [
            {"id": 201, "name": "출석률", "code": "AT1", "level": 2, "parent_id": 200},
            {"id": 202, "name": "발표 횟수", "code": "PR1", "level": 2, "parent_id": 200},
            {"id": 203, "name": "질문 횟수", "code": "QA1", "level": 2, "parent_id": 200}
        ],
        300: [
            {"id": 301, "name": "기술 성장", "code": "TG1", "level": 2, "parent_id": 300},
            {"id": 302, "name": "지식 확장", "code": "KE1", "level": 2, "parent_id": 300},
            {"id": 303, "name": "문제 해결력", "code": "PS1", "level": 2, "parent_id": 300}
        ],
        400: [
            {"id": 401, "name": "월간 활동", "code": "MA1", "level": 2, "parent_id": 400},
            {"id": 402, "name": "주간 활동", "code": "WA1", "level": 2, "parent_id": 400},
            {"id": 403, "name": "일일 활동", "code": "DA1", "level": 2, "parent_id": 400}
        ]
    }
    
    try:
        with conn.cursor() as cursor:
            # 부모 카테고리 삽입
            parent_sql = """
                INSERT INTO dashboard_category
                (dashboard_id, name, code, level, parent_id)
                VALUES (%s, %s, %s, %s, %s)
            """
            
            for parent in parent_categories:
                try:
                    cursor.execute(parent_sql, (
                        parent["id"], parent["name"], parent["code"], 
                        parent["level"], parent["parent_id"]
                    ))
                    dashboard_category_ids[parent["id"]] = []
                except Exception:
                    # 이미 존재하는 경우 무시
                    print(f"대시보드 카테고리 ID {parent['id']}는 이미 존재함")
                    dashboard_category_ids[parent["id"]] = []
                    continue
            
            conn.commit()
            
            # 자식 카테고리 삽입
            for parent_id, children in child_categories.items():
                for child in children:
                    try:
                        cursor.execute(parent_sql, (
                            child["id"], child["name"], child["code"], 
                            child["level"], child["parent_id"]
                        ))
                        dashboard_category_ids[parent_id].append(child["id"])
                    except Exception:
                        # 이미 존재하는 경우 무시
                        print(f"대시보드 카테고리 ID {child['id']}는 이미 존재함")
                        dashboard_category_ids[parent_id].append(child["id"])
                        continue
            
            conn.commit()
            
            # 대시보드 카테고리 개수 계산
            total_categories = len(dashboard_category_ids) + sum(len(children) for children in dashboard_category_ids.values())
            print(f"총 {total_categories}개의 대시보드 카테고리 데이터 삽입 완료!")
            
    finally:
        conn.close()
        
    return dashboard_category_ids

def insert_study_dashboards(member_ids, dashboard_categories, num_dashboards=5000):
    conn = get_connection()
    
    # 모든 대시보드 카테고리 ID 평탄화
    all_dashboard_ids = []
    for parent_id, child_ids in dashboard_categories.items():
        all_dashboard_ids.append(parent_id)
        all_dashboard_ids.extend(child_ids)
    
    try:
        with conn.cursor() as cursor:
            sql = """
                INSERT INTO study_dashboard
                (dashboard_id, member_id, argument, created_at, updated_at)
                VALUES (%s, %s, %s, %s, %s)
            """
            
            # 중복 방지를 위한 집합
            processed_pairs = set()
            count = 0
            
            while count < num_dashboards:
                dashboard_id = random.choice(all_dashboard_ids)
                member_id = random.choice(member_ids)
                
                # 중복 체크
                pair = (dashboard_id, member_id)
                if pair in processed_pairs:
                    continue
                
                processed_pairs.add(pair)
                
                # 대시보드 인자값 (0.0 ~ 100.0)
                argument = round(random.uniform(0.0, 100.0), 2)
                
                created_at = fake.date_time_between(start_date='-1y', end_date='-1m')
                updated_at = fake.date_time_between(start_date=created_at, end_date='now')
                
                cursor.execute(sql, (dashboard_id, member_id, argument, created_at, updated_at))
                count += 1
                
                if count % 1000 == 0:
                    conn.commit()
                    print(f"{count}개 스터디 대시보드 데이터 삽입됨.")
            
            conn.commit()
            print(f"총 {count}개의 스터디 대시보드 데이터 삽입 완료!")
            
    finally:
        conn.close() 