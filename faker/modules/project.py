from .common import get_connection, fake
import random
from datetime import datetime, timedelta

def insert_project_funcs():
    conn = get_connection()
    project_func_ids = []
    
    # 상위 기능들
    parent_funcs = [
        {"name": "프로젝트 관리", "description": "프로젝트 전반적인 관리 기능"},
        {"name": "사용자 관리", "description": "사용자 계정 및 권한 관리"},
        {"name": "콘텐츠 관리", "description": "콘텐츠 생성 및 관리"},
        {"name": "데이터 분석", "description": "데이터 수집 및 분석"},
        {"name": "시스템 관리", "description": "시스템 설정 및 유지보수"}
    ]
    
    # 각 상위 기능별 하위 기능들
    child_funcs = {
        "프로젝트 관리": [
            "일정 관리", "자원 관리", "비용 관리", "리스크 관리", "품질 관리"
        ],
        "사용자 관리": [
            "회원가입", "로그인", "프로필 관리", "권한 설정", "활동 로그"
        ],
        "콘텐츠 관리": [
            "게시물 작성", "댓글 관리", "미디어 업로드", "태그 관리", "검색 기능"
        ],
        "데이터 분석": [
            "데이터 수집", "데이터 처리", "시각화", "보고서 생성", "예측 분석"
        ],
        "시스템 관리": [
            "백업", "모니터링", "성능 최적화", "보안 관리", "API 관리"
        ]
    }
    
    try:
        with conn.cursor() as cursor:
            # 상위 기능 삽입
            parent_sql = """
                INSERT INTO project_func 
                (name, description, parent_id, created_at, updated_at)
                VALUES (%s, %s, %s, %s, %s)
            """
            
            parent_ids = {}
            
            for parent in parent_funcs:
                created_at = fake.date_time_between(start_date='-1y', end_date='now')
                updated_at = created_at
                
                cursor.execute(parent_sql, (
                    parent["name"], 
                    parent["description"], 
                    None,  # 상위 기능은 parent_id가 없음
                    created_at,
                    updated_at
                ))
                
                parent_id = cursor.lastrowid
                parent_ids[parent["name"]] = parent_id
                project_func_ids.append(parent_id)
            
            # 하위 기능 삽입
            child_sql = """
                INSERT INTO project_func 
                (name, description, parent_id, created_at, updated_at)
                VALUES (%s, %s, %s, %s, %s)
            """
            
            for parent_name, children in child_funcs.items():
                parent_id = parent_ids[parent_name]
                
                for child_name in children:
                    description = f"{parent_name}의 하위 기능: {child_name}"
                    created_at = fake.date_time_between(start_date='-1y', end_date='now')
                    updated_at = created_at
                    
                    cursor.execute(child_sql, (
                        child_name,
                        description,
                        parent_id,
                        created_at,
                        updated_at
                    ))
                    
                    child_id = cursor.lastrowid
                    project_func_ids.append(child_id)
            
            conn.commit()
            print(f"총 {len(project_func_ids)}개의 프로젝트 기능 데이터 삽입 완료!")
            
    finally:
        conn.close()
        
    return project_func_ids

def insert_comments(member_ids, project_func_ids, num_comments=3000):
    conn = get_connection()
    
    try:
        with conn.cursor() as cursor:
            # 먼저 기능의 부모/자식 관계를 파악
            cursor.execute("SELECT project_func_id, parent_id FROM project_func")
            func_relations = {}
            for func_id, parent_id in cursor.fetchall():
                func_relations[func_id] = parent_id
            
            # 댓글 삽입
            sql = """
                INSERT INTO comment 
                (member_id, project_func_id, parent_id, content, created_at, updated_at, is_deleted)
                VALUES (%s, %s, %s, %s, %s, %s, %s)
            """
            
            parent_comments = []  # 부모 댓글을 저장할 리스트
            
            for i in range(num_comments):
                member_id = random.choice(member_ids)
                project_func_id = random.choice(project_func_ids)
                
                # 70%는 부모 댓글, 30%는 자식 댓글
                is_parent = random.random() < 0.7 or not parent_comments
                
                if is_parent:
                    parent_id = None
                    content = fake.paragraph(nb_sentences=random.randint(1, 3))
                else:
                    # 부모 댓글 중에서 선택
                    parent_comment = random.choice(parent_comments)
                    parent_id = parent_comment["id"]
                    project_func_id = parent_comment["project_func_id"]  # 부모 댓글의 project_func_id 상속
                    content = fake.sentence()
                
                created_at = fake.date_time_between(start_date='-1y', end_date='now')
                updated_at = created_at
                is_deleted = 'FALSE' if random.random() < 0.95 else 'TRUE'
                
                cursor.execute(sql, (
                    member_id, 
                    project_func_id, 
                    parent_id, 
                    content, 
                    created_at, 
                    updated_at, 
                    is_deleted
                ))
                
                comment_id = cursor.lastrowid
                
                # 부모 댓글이면 리스트에 추가
                if is_parent:
                    parent_comments.append({
                        "id": comment_id,
                        "project_func_id": project_func_id
                    })
                
                if (i + 1) % 500 == 0:
                    conn.commit()
                    print(f"{i + 1}개 댓글 데이터 삽입됨.")
            
            conn.commit()
            print(f"총 {num_comments}개의 댓글 데이터 삽입 완료!")
            
    finally:
        conn.close()

def insert_member_ratings(member_ids, project_func_ids, num_ratings=5000):
    conn = get_connection()
    
    try:
        with conn.cursor() as cursor:
            sql = """
                INSERT INTO member_rating 
                (member_id, project_func_id, score, created_at, updated_at)
                VALUES (%s, %s, %s, %s, %s)
            """
            
            # 중복 체크를 위한 set
            processed_pairs = set()
            
            for i in range(num_ratings):
                member_id = random.choice(member_ids)
                project_func_id = random.choice(project_func_ids)
                
                # 중복 체크
                pair = (member_id, project_func_id)
                if pair in processed_pairs:
                    continue
                
                processed_pairs.add(pair)
                
                # 1.0 ~ 5.0 사이의 평점 (0.5 단위)
                score = round(random.uniform(1.0, 5.0) * 2) / 2
                
                created_at = fake.date_time_between(start_date='-1y', end_date='now')
                updated_at = created_at
                
                cursor.execute(sql, (member_id, project_func_id, score, created_at, updated_at))
                
                if (i + 1) % 500 == 0:
                    conn.commit()
                    print(f"{i + 1}개 회원 평점 데이터 삽입됨.")
            
            conn.commit()
            print(f"총 {len(processed_pairs)}개의 회원 평점 데이터 삽입 완료!")
            
    finally:
        conn.close()

def insert_member_points(member_ids, num_points=8000):
    conn = get_connection()
    
    try:
        with conn.cursor() as cursor:
            sql = """
                INSERT INTO member_point 
                (member_id, amount, reason, created_at)
                VALUES (%s, %s, %s, %s)
            """
            
            reasons = [
                "회원가입 보너스", "로그인 보너스", "프로젝트 참여", "댓글 작성", 
                "평가 참여", "추천인", "이벤트 참여", "미션 완료", "퀘스트 완료", "출석 체크"
            ]
            
            for i in range(num_points):
                member_id = random.choice(member_ids)
                
                # 대부분 양수, 간혹 음수 포인트
                if random.random() < 0.8:
                    amount = random.randint(10, 10000)
                    reason = random.choice(reasons)
                else:
                    amount = -random.randint(10, 1000)
                    reason = "포인트 사용"
                
                created_at = fake.date_time_between(start_date='-1y', end_date='now')
                
                cursor.execute(sql, (member_id, amount, reason, created_at))
                
                if (i + 1) % 500 == 0:
                    conn.commit()
                    print(f"{i + 1}개 회원 포인트 데이터 삽입됨.")
            
            conn.commit()
            print(f"총 {num_points}개의 회원 포인트 데이터 삽입 완료!")
            
    finally:
        conn.close()

def insert_experiences(member_ids, project_func_ids, num_experiences=10000):
    conn = get_connection()
    
    try:
        with conn.cursor() as cursor:
            sql = """
                INSERT INTO experience 
                (member_id, project_func_id, amount, reason, created_at)
                VALUES (%s, %s, %s, %s, %s)
            """
            
            reasons = [
                "프로젝트 참여", "댓글 작성", "문제 해결", "코드 기여", 
                "문서 작성", "테스트 참여", "코드 리뷰", "멘토링", "스터디 참여", "기술 블로그 작성"
            ]
            
            for i in range(num_experiences):
                member_id = random.choice(member_ids)
                
                # 90%는 project_func_id가 있고, 10%는 NULL
                if random.random() < 0.9:
                    project_func_id = random.choice(project_func_ids)
                else:
                    project_func_id = None
                
                amount = random.randint(10, 1000)
                reason = random.choice(reasons)
                created_at = fake.date_time_between(start_date='-1y', end_date='now')
                
                cursor.execute(sql, (member_id, project_func_id, amount, reason, created_at))
                
                if (i + 1) % 500 == 0:
                    conn.commit()
                    print(f"{i + 1}개 경험치 데이터 삽입됨.")
            
            conn.commit()
            print(f"총 {num_experiences}개의 경험치 데이터 삽입 완료!")
            
    finally:
        conn.close()

def insert_retrospects(member_ids, project_func_ids, num_retrospects=2000):
    conn = get_connection()
    
    try:
        with conn.cursor() as cursor:
            sql = """
                INSERT INTO retrospect 
                (member_id, project_func_id, content, created_at, updated_at, is_deleted)
                VALUES (%s, %s, %s, %s, %s, %s)
            """
            
            for i in range(num_retrospects):
                member_id = random.choice(member_ids)
                project_func_id = random.choice(project_func_ids)
                
                # 회고 내용 생성
                content_parts = []
                
                # Keep (잘한 점)
                keep = ["잘한 점:\n"]
                for _ in range(random.randint(1, 3)):
                    keep.append(f"- {fake.sentence()}")
                content_parts.append("\n".join(keep))
                
                # Problem (문제점)
                problem = ["\n\n문제점:\n"]
                for _ in range(random.randint(1, 3)):
                    problem.append(f"- {fake.sentence()}")
                content_parts.append("\n".join(problem))
                
                # Try (시도할 점)
                try_part = ["\n\n시도할 점:\n"]
                for _ in range(random.randint(1, 3)):
                    try_part.append(f"- {fake.sentence()}")
                content_parts.append("\n".join(try_part))
                
                content = "".join(content_parts)
                
                created_at = fake.date_time_between(start_date='-1y', end_date='-1d')
                updated_at = fake.date_time_between(start_date=created_at, end_date='now')
                is_deleted = 'FALSE' if random.random() < 0.95 else 'TRUE'
                
                cursor.execute(sql, (member_id, project_func_id, content, created_at, updated_at, is_deleted))
                
                if (i + 1) % 500 == 0:
                    conn.commit()
                    print(f"{i + 1}개 회고 데이터 삽입됨.")
            
            conn.commit()
            print(f"총 {num_retrospects}개의 회고 데이터 삽입 완료!")
            
    finally:
        conn.close() 