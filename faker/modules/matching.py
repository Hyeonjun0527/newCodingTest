from .common import get_connection, fake
import random
from datetime import datetime, timedelta

def insert_matching_fields():
    conn = get_connection()
    
    # 매칭 필드 예시
    matching_fields = [
        {"name": "기술 역량", "weight": 30},
        {"name": "프로젝트 경험", "weight": 25},
        {"name": "활동 빈도", "weight": 15},
        {"name": "응답률", "weight": 10},
        {"name": "평판 점수", "weight": 10},
        {"name": "지역 근접성", "weight": 5},
        {"name": "시간대 일치", "weight": 5}
    ]
    
    try:
        with conn.cursor() as cursor:
            sql = """
                INSERT INTO matching_field 
                (field_name, weight, created_at, updated_at)
                VALUES (%s, %s, %s, %s)
            """
            
            for field in matching_fields:
                created_at = fake.date_time_between(start_date='-2y', end_date='-6m')
                updated_at = fake.date_time_between(start_date=created_at, end_date='now')
                
                cursor.execute(sql, (field["name"], field["weight"], created_at, updated_at))

            conn.commit()
            print(f"총 {len(matching_fields)}개의 매칭 필드 데이터 삽입 완료!")
            
    finally:
        conn.close()

def insert_skill_categories():
    conn = get_connection()
    skill_category_ids = {}  # {parent_id: [child_ids]}
    
    # 상위 스킬 카테고리
    parent_categories = [
        {"name": "프로그래밍 언어", "code": "PRL"},
        {"name": "프레임워크", "code": "FRW"},
        {"name": "데이터베이스", "code": "DBM"},
        {"name": "운영체제", "code": "OPS"},
        {"name": "도구 및 유틸리티", "code": "TLS"}
    ]
    
    # 하위 스킬 카테고리 (상위 카테고리별)
    child_categories = {
        "프로그래밍 언어": [
            {"name": "Java", "code": "JAV"},
            {"name": "Python", "code": "PYT"},
            {"name": "JavaScript", "code": "JVS"},
            {"name": "C/C++", "code": "CPP"},
            {"name": "Go", "code": "GOL"}
        ],
        "프레임워크": [
            {"name": "Spring", "code": "SPR"},
            {"name": "React", "code": "RCT"},
            {"name": "Django", "code": "DJG"},
            {"name": "Vue.js", "code": "VUE"},
            {"name": "Flutter", "code": "FLT"}
        ],
        "데이터베이스": [
            {"name": "MySQL", "code": "SQL"},
            {"name": "MongoDB", "code": "MDB"},
            {"name": "PostgreSQL", "code": "PSQ"},
            {"name": "Redis", "code": "RDS"},
            {"name": "Firebase", "code": "FBS"}
        ],
        "운영체제": [
            {"name": "Linux", "code": "LNX"},
            {"name": "Windows", "code": "WIN"},
            {"name": "macOS", "code": "MAC"},
            {"name": "Docker", "code": "DOC"},
            {"name": "Kubernetes", "code": "K8S"}
        ],
        "도구 및 유틸리티": [
            {"name": "Git", "code": "GIT"},
            {"name": "AWS", "code": "AWS"},
            {"name": "CI/CD", "code": "CIC"},
            {"name": "Jira", "code": "JRA"},
            {"name": "Slack", "code": "SLK"}
        ]
    }
    
    try:
        with conn.cursor() as cursor:
            # 부모 카테고리 삽입
            parent_sql = """
                INSERT INTO skill_category 
                (skill_type_name, code, depth, parent_id)
                VALUES (%s, %s, %s, %s)
            """
            
            for parent in parent_categories:
                cursor.execute(parent_sql, (parent["name"], parent["code"], 0, None))
                parent_id = cursor.lastrowid
                skill_category_ids[parent_id] = []
                
                # 해당 부모 카테고리에 속하는 자식 카테고리 삽입
                if parent["name"] in child_categories:
                    for child in child_categories[parent["name"]]:
                        cursor.execute(parent_sql, (child["name"], child["code"], 1, parent_id))
                        child_id = cursor.lastrowid
                        skill_category_ids[parent_id].append(child_id)
            
            conn.commit()
            
            # 스킬 카테고리 개수 계산
            total_categories = len(skill_category_ids) + sum(len(children) for children in skill_category_ids.values())
            print(f"총 {total_categories}개의 스킬 카테고리 데이터 삽입 완료!")
            
    finally:
        conn.close()
        
    return skill_category_ids

def insert_matching_templates():
    conn = get_connection()
    template_ids = []
    
    # 미리 정의된 템플릿 목록
    templates = [
        {"name": "웹 개발 프로젝트", "description": "웹 애플리케이션 개발을 위한 매칭 템플릿입니다."},
        {"name": "모바일 앱 개발", "description": "모바일 애플리케이션 개발을 위한 매칭 템플릿입니다."},
        {"name": "데이터 분석 프로젝트", "description": "데이터 분석 및 시각화를 위한 매칭 템플릿입니다."},
        {"name": "디자인 프로젝트", "description": "UI/UX 디자인을 위한 매칭 템플릿입니다."},
        {"name": "인프라 구축 프로젝트", "description": "클라우드 인프라 구축을 위한 매칭 템플릿입니다."},
        {"name": "백엔드 개발 특화", "description": "백엔드 시스템 개발에 특화된 매칭 템플릿입니다."},
        {"name": "프론트엔드 개발 특화", "description": "프론트엔드 개발에 특화된 매칭 템플릿입니다."},
        {"name": "풀스택 개발 프로젝트", "description": "풀스택 개발을 위한 매칭 템플릿입니다."},
        {"name": "소규모 스타트업 프로젝트", "description": "소규모 스타트업을 위한 매칭 템플릿입니다."},
        {"name": "대규모 엔터프라이즈 프로젝트", "description": "대규모 엔터프라이즈 시스템을 위한 매칭 템플릿입니다."}
    ]
    
    try:
        with conn.cursor() as cursor:
            sql = """
                INSERT INTO matching_template 
                (name, description, created_at, updated_at)
                VALUES (%s, %s, %s, %s)
            """
            
            for template in templates:
                created_at = fake.date_time_between(start_date='-1y', end_date='-1d')
                updated_at = fake.date_time_between(start_date=created_at, end_date='now')
                
                cursor.execute(sql, (template["name"], template["description"], created_at, updated_at))
                template_ids.append(cursor.lastrowid)
            
            conn.commit()
            print(f"총 {len(templates)}개의 매칭 템플릿 데이터 삽입 완료!")
            
    finally:
        conn.close()
        
    return template_ids

def insert_matching_template_details(template_ids, matching_field_ids, skill_category_ids):
    conn = get_connection()
    
    try:
        with conn.cursor() as cursor:
            sql = """
                INSERT INTO matching_template_detail 
                (matching_template_id, matching_field_id, field_value, skill_category_id)
                VALUES (%s, %s, %s, %s)
            """
            
            count = 0
            for template_id in template_ids:
                # 각 템플릿마다 2~5개의 매칭 필드 사용
                selected_field_ids = random.sample(matching_field_ids, random.randint(2, min(5, len(matching_field_ids))))
                
                for field_id in selected_field_ids:
                    # 필드 값은 1~10 사이의 랜덤 값
                    field_value = random.randint(1, 10)
                    
                    # 스킬 카테고리는 모든 상위 카테고리에서 랜덤하게 선택
                    skill_category_choices = []
                    for parent, data in skill_category_ids.items():
                        skill_category_choices.append(data["id"])  # 상위 카테고리
                        skill_category_choices.extend(data["children"])  # 하위 카테고리
                    
                    skill_category_id = random.choice(skill_category_choices)
                    
                    cursor.execute(sql, (template_id, field_id, field_value, skill_category_id))
                    count += 1
            
            conn.commit()
            print(f"총 {count}개의 매칭 템플릿 상세 데이터 삽입 완료!")
            
    finally:
        conn.close()

def insert_matching_requests(member_ids, template_ids, num_requests=2000):
    conn = get_connection()
    matching_request_ids = []
    status_options = ['PENDING', 'ACCEPTED', 'CANCELED', 'REJECTED', 'AUTO', 'DONE']
    type_options = ['AUTO', 'MANUAL']
    deleted_options = ['TRUE', 'FALSE']
    
    try:
        with conn.cursor() as cursor:
            sql = """
                INSERT INTO matching_request
                (member_id, partner_id, template_id, status, type, content, deleted, created_at, updated_at)
                VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s)
            """
            
            for i in range(num_requests):
                member_id = random.choice(member_ids)
                
                # 파트너 ID는 NULL일 수 있음 (자동 매칭 중일 경우)
                partner_id = None
                if random.random() < 0.7:  # 70%는 파트너가 지정됨
                    # 자기 자신이 아닌 다른 멤버를 선택
                    potential_partners = [mid for mid in member_ids if mid != member_id]
                    partner_id = random.choice(potential_partners)
                
                template_id = random.choice(template_ids)
                status = random.choice(status_options)
                request_type = random.choice(type_options)
                
                # 매칭 유형에 따라 파트너 ID 조정
                if request_type == 'AUTO':
                    status = 'AUTO'  # 자동 매칭은 AUTO 상태
                    partner_id = None  # 자동 매칭은 파트너가 아직 없음
                
                content = fake.sentence(nb_words=5)
                deleted = 'FALSE'
                if status in ['CANCELED', 'REJECTED'] and random.random() < 0.3:
                    deleted = 'TRUE'
                
                created_at = fake.date_time_between(start_date='-1y', end_date='-1d')
                updated_at = fake.date_time_between(start_date=created_at, end_date='now')
                
                cursor.execute(sql, (
                    member_id, partner_id, template_id, status, request_type, 
                    content, deleted, created_at, updated_at
                ))
                matching_request_ids.append(cursor.lastrowid)
                
                if (i + 1) % 500 == 0:
                    conn.commit()
                    print(f"{i + 1}개 매칭 요청 데이터 삽입됨.")

            conn.commit()
            print(f"총 {len(matching_request_ids)}개의 매칭 요청 데이터 삽입 완료!")
            
    finally:
        conn.close()
        
    return matching_request_ids

def insert_matching_request_partners(matching_request_ids, member_ids):
    conn = get_connection()
    status_options = ['DONE', 'CANCEL']
    
    # 완료된 매칭 요청만 가져오기 (상태가 'DONE'인 것들)
    matching_requests_with_partners = {}
    
    try:
        with conn.cursor() as cursor:
            # 매칭 요청 상태 조회
            query = """
                SELECT matching_id, status, member_id
                FROM matching_request
                WHERE matching_id IN ({})
            """.format(','.join(['%s'] * len(matching_request_ids)))
            
            cursor.execute(query, matching_request_ids)
            results = cursor.fetchall()
            
            for matching_id, status, member_id in results:
                if status in ['DONE', 'ACCEPTED']:
                    matching_requests_with_partners[matching_id] = member_id
            
            # 매칭 요청 파트너 삽입
            insert_sql = """
                INSERT INTO matching_request_partner
                (matching_id, partner_id, status, cancel_reason, matched_at, updated_at)
                VALUES (%s, %s, %s, %s, %s, %s)
            """
            
            count = 0
            for matching_id, requester_id in matching_requests_with_partners.items():
                # 요청자가 아닌 다른 멤버를 파트너로 선택
                potential_partners = [mid for mid in member_ids if mid != requester_id]
                partner_id = random.choice(potential_partners)
                
                status = random.choices(status_options, weights=[0.8, 0.2])[0]  # 80% DONE, 20% CANCEL
                cancel_reason = None
                if status == 'CANCEL':
                    cancel_reason = random.choice([
                        "일정 변경", "다른 파트너 찾음", "요구사항 불일치", 
                        "개인 사정", "연락 두절", "기술 역량 불일치"
                    ])
                
                matched_at = fake.date_time_between(start_date='-6m', end_date='-1d')
                updated_at = fake.date_time_between(start_date=matched_at, end_date='now')
                
                cursor.execute(insert_sql, (
                    matching_id, partner_id, status, cancel_reason, matched_at, updated_at
                ))
                count += 1

            conn.commit()
            print(f"총 {count}개의 매칭 요청 파트너 데이터 삽입 완료!")
            
    finally:
        conn.close()
