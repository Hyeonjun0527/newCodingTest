from faker import Faker
import pymysql
import random
import uuid

fake = Faker('ko_KR')

# 전역 변수로 테이블 목록 정의
TABLES = {
    'member': '회원',
    'image': '이미지',
    'resized_image': '리사이즈 이미지',
    'member_profile': '회원 프로필',
    'member_detail': '회원 상세정보',
    'blacklist': '블랙리스트',
    'matching_field': '매칭 필드',
    'skill_category': '기술 카테고리',
    'matching_template': '매칭 템플릿',
    'matching_template_detail': '매칭 템플릿 상세',
    'matching_request': '매칭 요청',
    'matching_request_partner': '매칭 요청 파트너',
    'notification_category': '알림 카테고리',
    'notification_setting': '알림 설정',
    'notification': '알림',
    'notification_reservation': '알림 예약',
    'social_media_type': '소셜 미디어 타입',
    'social_media': '소셜 미디어',
    'tech_stack': '기술 스택',
    'tech_stack_ref': '기술 스택 참조',
    'project_func': '프로젝트 기능',
    'comment': '댓글',
    'member_rating': '회원 평점',
    'member_point': '회원 포인트',
    'experience': '경험치',
    'retrospect': '회고',
    'follow': '팔로우',
    'study_space': '스터디 공간',
    'daily_study_content': '일일 스터디 내용',
    'attendance': '출석',
    'dashboard_category': '대시보드 카테고리',
    'study_dashboard': '스터디 대시보드'
}

# 외래 키 종속성을 고려한 테이블 순서 (삭제 시 사용)
TRUNCATE_ORDER = [
    'study_dashboard',
    'dashboard_category',
    'attendance',
    'daily_study_content',
    'study_space',
    'follow',
    'retrospect',
    'notification',
    'notification_reservation',
    'notification_setting',
    'notification_category',
    'matching_request_partner',
    'matching_request',
    'matching_template_detail',
    'matching_template',
    'tech_stack_ref',
    'tech_stack',
    'social_media',
    'social_media_type',
    'experience',
    'member_point',
    'member_rating',
    'comment',
    'blacklist',
    'member_detail',
    'member_profile',
    'skill_category',
    'matching_field',
    'resized_image',
    'image',
    'member'
]

def get_connection():
    return pymysql.connect(
        host='localhost',
        user='root',
        password='root',            # 본인 비밀번호로 변경해야 함
        database='zto_local_core',  # 실제로 만든 DB 이름
        charset='utf8mb4'
    )

def truncate_tables():
    conn = get_connection()
    
    try:
        with conn.cursor() as cursor:
            # 외래 키 제약 조건 비활성화
            cursor.execute("SET FOREIGN_KEY_CHECKS = 0")
            
            # 테이블 비우기
            for table in TRUNCATE_ORDER:
                cursor.execute(f"TRUNCATE TABLE {table}")
                print(f"{table} 테이블 비우기 완료")
            
            # 외래 키 제약 조건 다시 활성화
            cursor.execute("SET FOREIGN_KEY_CHECKS = 1")
            
            conn.commit()
            print("모든 테이블 비우기 완료!")
            
    except Exception as e:
        print(f"테이블 비우기 중 오류 발생: {e}")
        conn.rollback()
        
    finally:
        conn.close()

def insert_members(num_records=10000):
    conn = get_connection()
    member_ids = []
    
    try:
        with conn.cursor() as cursor:
            sql = """
                INSERT INTO member 
                (login_id, phone, name, created_at, updated_at, member_status, auto_matching, role)
                VALUES (%s, %s, %s, %s, %s, %s, %s, %s)
            """

            for i in range(num_records):
                login_id = fake.unique.user_name()
                phone = fake.phone_number()
                name = fake.name()
                created_at = fake.date_time_between(start_date='-2y', end_date='now')
                updated_at = created_at

                member_status = random.choice(['ACTIVE', 'INACTIVE'])
                auto_matching = random.choice(['T', 'F'])
                role = 'ROLE_MEMBER'

                cursor.execute(sql, (login_id, phone, name, created_at, updated_at, member_status, auto_matching, role))
                member_ids.append(cursor.lastrowid)

                if (i + 1) % 1000 == 0:
                    conn.commit()
                    print(f"{i + 1}개 멤버 데이터 삽입됨.")

            conn.commit()
            print(f"총 {num_records}개의 멤버 데이터 삽입 완료!")
            
    finally:
        conn.close()
        
    return member_ids

def insert_images(num_images=5000):
    conn = get_connection()
    image_ids = []
    
    try:
        with conn.cursor() as cursor:
            sql = """
                INSERT INTO image 
                (original_image_url, created_at, updated_at)
                VALUES (%s, %s, %s)
            """

            for i in range(num_images):
                image_uuid = str(uuid.uuid4())
                original_image_url = f"https://example.com/images/original/{image_uuid}.jpg"
                created_at = fake.date_time_between(start_date='-2y', end_date='now')
                updated_at = created_at

                cursor.execute(sql, (original_image_url, created_at, updated_at))
                image_ids.append(cursor.lastrowid)

                if (i + 1) % 1000 == 0:
                    conn.commit()
                    print(f"{i + 1}개 이미지 데이터 삽입됨.")

            conn.commit()
            print(f"총 {num_images}개의 이미지 데이터 삽입 완료!")
            
    finally:
        conn.close()
        
    return image_ids

def insert_resized_images(image_ids):
    conn = get_connection()
    resize_types = ['THUMB', 'SMALL', 'LARGE', 'ETC']
    
    try:
        with conn.cursor() as cursor:
            sql = """
                INSERT INTO resized_image 
                (image_id, resized_image_url, resizing_type)
                VALUES (%s, %s, %s)
            """

            count = 0
            for image_id in image_ids:
                # 각 이미지마다 1~4개의 리사이즈 이미지 생성
                for resize_type in random.sample(resize_types, random.randint(1, len(resize_types))):
                    image_uuid = str(uuid.uuid4())
                    resized_image_url = f"https://example.com/images/{resize_type.lower()}/{image_uuid}.jpg"
                    
                    cursor.execute(sql, (image_id, resized_image_url, resize_type))
                    count += 1

                    if count % 1000 == 0:
                        conn.commit()
                        print(f"{count}개 리사이즈 이미지 데이터 삽입됨.")

            conn.commit()
            print(f"총 {count}개의 리사이즈 이미지 데이터 삽입 완료!")
            
    finally:
        conn.close()

def insert_member_profiles(member_ids, image_ids):
    conn = get_connection()
    
    try:
        with conn.cursor() as cursor:
            sql = """
                INSERT INTO member_profile 
                (member_id, nickname, profile_intro, image_id, created_at, updated_at)
                VALUES (%s, %s, %s, %s, %s, %s)
            """

            count = 0
            for member_id in member_ids:
                # 약 80%의 멤버만 프로필을 가지도록 설정
                if random.random() < 0.8:
                    nickname = fake.user_name()
                    profile_intro = fake.sentence(nb_words=10)
                    
                    # 약 70%의 프로필만 이미지를 가지도록 설정
                    image_id = random.choice(image_ids) if random.random() < 0.7 else None
                    
                    created_at = fake.date_time_between(start_date='-2y', end_date='now')
                    updated_at = fake.date_time_between(start_date=created_at, end_date='now')
                    
                    cursor.execute(sql, (member_id, nickname, profile_intro, image_id, created_at, updated_at))
                    count += 1

                    if count % 1000 == 0:
                        conn.commit()
                        print(f"{count}개 프로필 데이터 삽입됨.")

            conn.commit()
            print(f"총 {count}개의 프로필 데이터 삽입 완료!")
            
    finally:
        conn.close()
        
    return [member_id for member_id in member_ids if random.random() < 0.8]  # 프로필이 생성된 멤버 ID만 반환

def insert_social_media_types(image_ids, num_types=10):
    conn = get_connection()
    social_media_type_ids = []
    
    # 소셜 미디어 타입 예시
    social_media_types = [
        "Facebook", "Instagram", "Twitter", "LinkedIn", "GitHub",
        "YouTube", "TikTok", "Pinterest", "Reddit", "Snapchat",
        "Medium", "Discord", "Twitch", "WeChat", "Telegram"
    ]
    
    try:
        with conn.cursor() as cursor:
            sql = """
                INSERT INTO social_media_type 
                (type_name, description, image_id)
                VALUES (%s, %s, %s)
            """

            # 사용할 소셜 미디어 타입 선택
            selected_types = random.sample(social_media_types, min(num_types, len(social_media_types)))
            
            for type_name in selected_types:
                description = f"{type_name} 소셜 미디어 플랫폼"
                # 약 50%의 소셜 미디어 타입만 이미지를 가지도록 설정
                image_id = random.choice(image_ids) if random.random() < 0.5 else None
                
                cursor.execute(sql, (type_name, description, image_id))
                social_media_type_ids.append(cursor.lastrowid)
                print(f"{type_name} 소셜 미디어 타입 삽입됨.")

            conn.commit()
            print(f"총 {len(social_media_type_ids)}개의 소셜 미디어 타입 데이터 삽입 완료!")
            
    finally:
        conn.close()
        
    return social_media_type_ids

def insert_social_media(member_profile_ids, social_media_type_ids, num_records=3000):
    conn = get_connection()
    
    try:
        with conn.cursor() as cursor:
            sql = """
                INSERT INTO social_media 
                (member_id, social_media_type_id, url, created_at, updated_at)
                VALUES (%s, %s, %s, %s, %s)
            """

            count = 0
            # 무작위로 회원별 소셜미디어 생성 (중복 없이)
            processed_pairs = set()
            
            while count < num_records and len(processed_pairs) < len(member_profile_ids) * len(social_media_type_ids):
                member_id = random.choice(member_profile_ids)
                social_media_type_id = random.choice(social_media_type_ids)
                
                # 같은 회원이 같은 소셜 미디어 타입을 중복해서 가지지 않도록
                pair = (member_id, social_media_type_id)
                if pair in processed_pairs:
                    continue
                
                processed_pairs.add(pair)
                
                url = f"https://social-media-{social_media_type_id}.com/user/{fake.user_name()}"
                created_at = fake.date_time_between(start_date='-1y', end_date='now')
                updated_at = fake.date_time_between(start_date=created_at, end_date='now')
                
                cursor.execute(sql, (member_id, social_media_type_id, url, created_at, updated_at))
                count += 1

                if count % 1000 == 0:
                    conn.commit()
                    print(f"{count}개 소셜 미디어 데이터 삽입됨.")

            conn.commit()
            print(f"총 {count}개의 소셜 미디어 데이터 삽입 완료!")
            
    finally:
        conn.close()

def insert_tech_stacks(image_ids, num_parent_stacks=10, num_child_stacks_per_parent=5):
    conn = get_connection()
    tech_stack_ids = {}  # {parent_id: [child_ids]} 형태로 저장
    
    # 기술 스택 예시 (부모)
    parent_tech_stacks = [
        "프론트엔드", "백엔드", "데이터베이스", "데브옵스", "모바일",
        "인공지능", "블록체인", "보안", "게임 개발", "클라우드",
        "임베디드", "빅데이터", "IoT", "네트워크", "UI/UX"
    ]
    
    # 자식 기술 스택 예시 (각 부모별)
    child_tech_stacks = {
        "프론트엔드": ["React", "Vue.js", "Angular", "Next.js", "Svelte", "HTML/CSS", "JavaScript", "TypeScript"],
        "백엔드": ["Spring", "Django", "Node.js", "Express", "Flask", "Laravel", "ASP.NET", "Ruby on Rails"],
        "데이터베이스": ["MySQL", "PostgreSQL", "MongoDB", "Redis", "Oracle", "SQL Server", "Firebase", "DynamoDB"],
        "데브옵스": ["Docker", "Kubernetes", "Jenkins", "GitLab CI", "AWS", "Azure", "GCP", "Terraform"],
        "모바일": ["Android", "iOS", "React Native", "Flutter", "Xamarin", "Kotlin", "Swift", "Objective-C"],
        "인공지능": ["TensorFlow", "PyTorch", "scikit-learn", "Keras", "NLTK", "OpenCV", "Pandas", "NumPy"],
        "블록체인": ["Ethereum", "Solidity", "Bitcoin", "Hyperledger", "Web3.js", "Smart Contracts", "NFT", "DeFi"],
        "보안": ["암호화", "네트워크 보안", "인증", "권한 관리", "취약점 분석", "침투 테스트", "OWASP", "방화벽"],
        "게임 개발": ["Unity", "Unreal Engine", "Godot", "Phaser", "WebGL", "DirectX", "OpenGL", "게임 AI"],
        "클라우드": ["AWS 서비스", "Azure 서비스", "GCP 서비스", "Serverless", "IaaS", "PaaS", "SaaS", "마이크로서비스"],
        "임베디드": ["C/C++", "임베디드 Linux", "Arduino", "Raspberry Pi", "RTOS", "Firmware", "ARM", "IoT 기기"],
        "빅데이터": ["Hadoop", "Spark", "Kafka", "Elasticsearch", "Hive", "Flink", "Tableau", "Power BI"],
        "IoT": ["MQTT", "CoAP", "Zigbee", "센서 네트워킹", "IoT 플랫폼", "임베디드 시스템", "스마트홈", "산업용 IoT"],
        "네트워크": ["TCP/IP", "HTTP/HTTPS", "REST API", "GraphQL", "gRPC", "WebSockets", "SDN", "VPN"],
        "UI/UX": ["Figma", "Adobe XD", "Sketch", "사용자 경험", "사용자 인터페이스", "웹 접근성", "반응형 디자인", "인터랙션 디자인"]
    }
    
    try:
        with conn.cursor() as cursor:
            # 부모 기술 스택 삽입
            parent_sql = """
                INSERT INTO tech_stack 
                (tech_stack_name, parent_id, level, image_id, created_at, updated_at)
                VALUES (%s, %s, %s, %s, %s, %s)
            """
            
            # 선택할 부모 기술 스택
            selected_parents = random.sample(parent_tech_stacks, min(num_parent_stacks, len(parent_tech_stacks)))
            
            for parent_name in selected_parents:
                # 이미지는 약 70%의 확률로 할당
                image_id = random.choice(image_ids) if random.random() < 0.7 else None
                created_at = fake.date_time_between(start_date='-2y', end_date='-6m')
                updated_at = fake.date_time_between(start_date=created_at, end_date='now')
                
                cursor.execute(parent_sql, (parent_name, None, 1, image_id, created_at, updated_at))
                parent_id = cursor.lastrowid
                tech_stack_ids[parent_id] = []
                
                # 해당 부모에 속하는 자식 기술 스택 선택 및 삽입
                if parent_name in child_tech_stacks:
                    available_children = child_tech_stacks[parent_name]
                    # 해당 부모에 대해 선택할 자식 기술 스택 수
                    num_children = min(num_child_stacks_per_parent, len(available_children))
                    selected_children = random.sample(available_children, num_children)
                    
                    for child_name in selected_children:
                        # 자식 이미지는 약 50%의 확률로 할당
                        child_image_id = random.choice(image_ids) if random.random() < 0.5 else None
                        child_created_at = fake.date_time_between(start_date=created_at, end_date='-3m')
                        child_updated_at = fake.date_time_between(start_date=child_created_at, end_date='now')
                        
                        cursor.execute(parent_sql, (child_name, parent_id, 2, child_image_id, child_created_at, child_updated_at))
                        child_id = cursor.lastrowid
                        tech_stack_ids[parent_id].append(child_id)
            
            conn.commit()
            
            # 기술 스택 개수 계산
            total_stacks = len(tech_stack_ids) + sum(len(children) for children in tech_stack_ids.values())
            print(f"총 {total_stacks}개의 기술 스택 데이터 삽입 완료!")
            
    finally:
        conn.close()
        
    return tech_stack_ids

def insert_tech_stack_refs(member_profile_ids, tech_stack_ids, refs_per_member_min=1, refs_per_member_max=5):
    conn = get_connection()
    
    # 모든 기술 스택 ID를 평면화
    all_tech_stack_ids = []
    for parent_id, child_ids in tech_stack_ids.items():
        all_tech_stack_ids.append(parent_id)
        all_tech_stack_ids.extend(child_ids)
    
    try:
        with conn.cursor() as cursor:
            sql = """
                INSERT INTO tech_stack_ref 
                (tech_stack_id, member_id)
                VALUES (%s, %s)
            """

            count = 0
            # 이미 처리된 (회원, 기술스택) 쌍 추적
            processed_pairs = set()
            
            for member_id in member_profile_ids:
                # 각 회원마다 1~5개의 기술 스택 참조를 생성
                num_refs = random.randint(refs_per_member_min, refs_per_member_max)
                
                # 선택 가능한 기술 스택 중에서 무작위로 선택
                for _ in range(num_refs):
                    tech_stack_id = random.choice(all_tech_stack_ids)
                    
                    # 중복 방지
                    pair = (member_id, tech_stack_id)
                    if pair in processed_pairs:
                        continue
                        
                    processed_pairs.add(pair)
                    
                    cursor.execute(sql, (tech_stack_id, member_id))
                    count += 1

                    if count % 1000 == 0:
                        conn.commit()
                        print(f"{count}개 기술 스택 참조 데이터 삽입됨.")

            conn.commit()
            print(f"총 {count}개의 기술 스택 참조 데이터 삽입 완료!")
            
    finally:
        conn.close()

def print_table_counts():
    conn = get_connection()
    
    try:
        with conn.cursor() as cursor:
            total_count = 0
            print("\n===== 테이블별 데이터 수 =====")
            
            # TABLES 딕셔너리의 키를 사용하여 각 테이블 순회
            for table, description in TABLES.items():
                cursor.execute(f"SELECT COUNT(*) FROM {table}")
                count = cursor.fetchone()[0]
                total_count += count
                print(f"{description}({table}): {count:,}개")
            
            print("===========================")
            print(f"총 데이터 수: {total_count:,}개")
            
    except Exception as e:
        print(f"데이터 수 조회 중 오류 발생: {e}")
        
    finally:
        conn.close()

def insert_member_details(member_ids):
    conn = get_connection()
    
    try:
        with conn.cursor() as cursor:
            sql = """
                INSERT INTO member_detail 
                (member_id, nickname, profile_image, bio, created_at, updated_at)
                VALUES (%s, %s, %s, %s, %s, %s)
            """

            count = 0
            for member_id in member_ids:
                # 약 40%의 멤버만 상세 정보를 가지도록 설정 (member_profile과 중복 피하기)
                if random.random() < 0.4:
                    nickname = fake.user_name()
                    profile_image = f"https://example.com/profiles/{fake.uuid4()}.jpg"
                    bio = fake.paragraph(nb_sentences=2)
                    
                    created_at = fake.date_time_between(start_date='-2y', end_date='-1m')
                    updated_at = fake.date_time_between(start_date=created_at, end_date='now')
                    
                    cursor.execute(sql, (member_id, nickname, profile_image, bio, created_at, updated_at))
                    count += 1

                    if count % 1000 == 0:
                        conn.commit()
                        print(f"{count}개 회원 상세정보 데이터 삽입됨.")

            conn.commit()
            print(f"총 {count}개의 회원 상세정보 데이터 삽입 완료!")
            
    finally:
        conn.close()

def insert_blacklist(member_ids, num_blacklist=100):
    conn = get_connection()
    blacklist_reasons = [
        "불건전한 활동", "규정 위반", "타 회원 신고", "서비스 악용", "유해 콘텐츠 게시",
        "스팸 활동", "부적절한 댓글", "사기 행위", "계정 탈취 시도", "중복 계정 사용"
    ]
    
    try:
        with conn.cursor() as cursor:
            sql = """
                INSERT INTO blacklist 
                (member_id, reason, created_at)
                VALUES (%s, %s, %s)
            """

            # 블랙리스트에 추가할 회원 무작위 선택 (총 회원의 약 1%)
            blacklist_member_ids = random.sample(member_ids, min(num_blacklist, len(member_ids)))
            
            for member_id in blacklist_member_ids:
                reason = random.choice(blacklist_reasons)
                created_at = fake.date_time_between(start_date='-1y', end_date='now')
                
                cursor.execute(sql, (member_id, reason, created_at))

            conn.commit()
            print(f"총 {len(blacklist_member_ids)}개의 블랙리스트 데이터 삽입 완료!")
            
    finally:
        conn.close()

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
    
    # 매칭 템플릿 예시
    templates = [
        {
            "name": "학습분야 우선 매칭",
            "description": "학습 분야와 기술 스택을 우선적으로 고려하는 매칭 템플릿"
        },
        {
            "name": "경험 우선 매칭",
            "description": "프로젝트 경험과 활동 이력을 우선적으로 고려하는 매칭 템플릿"
        },
        {
            "name": "평판 우선 매칭",
            "description": "사용자 평판과 평점을 우선적으로 고려하는 매칭 템플릿"
        },
        {
            "name": "활동성 우선 매칭", 
            "description": "활동 빈도와 응답률을 우선적으로 고려하는 매칭 템플릿"
        },
        {
            "name": "균형 매칭",
            "description": "모든 요소를 균형있게 고려하는 매칭 템플릿"
        }
    ]
    
    try:
        with conn.cursor() as cursor:
            sql = """
                INSERT INTO matching_template
                (name, description, created_at, updated_at)
                VALUES (%s, %s, %s, %s)
            """
            
            for template in templates:
                created_at = fake.date_time_between(start_date='-2y', end_date='-6m')
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
    operators = ['=', '>=', '<=', '!=', '>']
    
    try:
        with conn.cursor() as cursor:
            sql = """
                INSERT INTO matching_template_detail
                (template_id, matching_field_id, skill_type_id, weight, operator, value, order_seq, created_at, updated_at)
                VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s)
            """
            
            count = 0
            for template_id in template_ids:
                # 각 템플릿마다 2~5개의 매칭 필드 사용
                num_fields = random.randint(2, min(5, len(matching_field_ids)))
                selected_fields = random.sample(matching_field_ids, num_fields)
                
                for order_seq, field_id in enumerate(selected_fields, 1):
                    # 일부 필드는 스킬 카테고리 연결 (약 30%)
                    skill_type_id = None
                    if random.random() < 0.3 and skill_category_ids:
                        # 평탄화된 skill_category_ids 생성
                        flat_skill_ids = []
                        for parent_id, child_ids in skill_category_ids.items():
                            flat_skill_ids.append(parent_id)
                            flat_skill_ids.extend(child_ids)
                        
                        skill_type_id = random.choice(flat_skill_ids)
                    
                    weight = round(random.uniform(0.5, 5.0), 2)
                    operator = random.choice(operators)
                    
                    # 값 생성
                    if operator in ['=', '!=']:
                        value = str(random.randint(1, 10))
                    else:  # 범위 연산자
                        value = str(random.randint(3, 8))
                    
                    created_at = fake.date_time_between(start_date='-2y', end_date='-3m')
                    updated_at = fake.date_time_between(start_date=created_at, end_date='now')
                    
                    cursor.execute(sql, (
                        template_id, field_id, skill_type_id, weight, operator, 
                        value, order_seq, created_at, updated_at
                    ))
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

def insert_notification_categories():
    conn = get_connection()
    notification_category_ids = {}
    
    # 상위 알림 카테고리
    parent_categories = [
        {"name": "매칭 알림", "rank": 1},
        {"name": "시스템 알림", "rank": 2},
        {"name": "활동 알림", "rank": 3},
        {"name": "공지사항", "rank": 4}
    ]
    
    # 하위 알림 카테고리 (상위 카테고리별)
    child_categories = {
        "매칭 알림": [
            {"name": "매칭 요청", "rank": 1},
            {"name": "매칭 수락", "rank": 2},
            {"name": "매칭 거절", "rank": 3},
            {"name": "매칭 취소", "rank": 4},
            {"name": "매칭 완료", "rank": 5}
        ],
        "시스템 알림": [
            {"name": "계정 정보", "rank": 1},
            {"name": "보안 알림", "rank": 2},
            {"name": "업데이트 안내", "rank": 3}
        ],
        "활동 알림": [
            {"name": "팔로우", "rank": 1},
            {"name": "댓글", "rank": 2},
            {"name": "좋아요", "rank": 3},
            {"name": "멘션", "rank": 4}
        ],
        "공지사항": [
            {"name": "서비스 공지", "rank": 1},
            {"name": "이벤트 안내", "rank": 2}
        ]
    }
    
    try:
        with conn.cursor() as cursor:
            parent_sql = """
                INSERT INTO notification_category 
                (name, parent_id, child_id, rank)
                VALUES (%s, %s, %s, %s)
            """
            
            for parent in parent_categories:
                cursor.execute(parent_sql, (parent["name"], None, None, parent["rank"]))
                parent_id = cursor.lastrowid
                notification_category_ids[parent_id] = []
                
                # 해당 부모 카테고리에 속하는 자식 카테고리 삽입
                if parent["name"] in child_categories:
                    for child in child_categories[parent["name"]]:
                        cursor.execute(parent_sql, (child["name"], parent_id, None, child["rank"]))
                        child_id = cursor.lastrowid
                        notification_category_ids[parent_id].append(child_id)
                        
                        # 부모 카테고리의 child_id 업데이트 (첫 번째 자식으로)
                        if len(notification_category_ids[parent_id]) == 1:
                            update_sql = "UPDATE notification_category SET child_id = %s WHERE notification_category_id = %s"
                            cursor.execute(update_sql, (child_id, parent_id))
            
            conn.commit()
            
            # 알림 카테고리 개수 계산
            total_categories = len(notification_category_ids) + sum(len(children) for children in notification_category_ids.values())
            print(f"총 {total_categories}개의 알림 카테고리 데이터 삽입 완료!")
            
    finally:
        conn.close()
        
    return notification_category_ids

def insert_notification_settings(member_ids, notification_category_ids):
    conn = get_connection()
    count = 0
    
    try:
        with conn.cursor() as cursor:
            sql = """
                INSERT INTO notification_setting 
                (member_id, notification_category_id, status)
                VALUES (%s, %s, %s)
            """
            
            # 평탄화된 알림 카테고리 ID 리스트 생성
            flat_category_ids = []
            for parent_id, child_ids in notification_category_ids.items():
                flat_category_ids.append(parent_id)
                flat_category_ids.extend(child_ids)
            
            # 각 회원마다 일부 알림 카테고리에 대한 설정 생성
            for member_id in member_ids:
                # 약 40%의 회원만 알림 설정을 갖도록
                if random.random() < 0.4:
                    # 각 회원당 1~3개의 알림 카테고리 설정
                    num_settings = random.randint(1, min(3, len(flat_category_ids)))
                    selected_categories = random.sample(flat_category_ids, num_settings)
                    
                    for category_id in selected_categories:
                        status = random.choice(['ON', 'OFF'])
                        
                        try:
                            cursor.execute(sql, (member_id, category_id, status))
                            count += 1
                        except pymysql.IntegrityError as e:
                            # 중복 키 에러 무시(한 회원이 같은 카테고리에 여러 설정을 가질 수 없음)
                            continue
                            
                    if count % 1000 == 0 and count > 0:
                        conn.commit()
                        print(f"{count}개 알림 설정 데이터 삽입됨.")
            
            conn.commit()
            print(f"총 {count}개의 알림 설정 데이터 삽입 완료!")
            
    finally:
        conn.close()

def insert_notifications(member_ids, notification_category_ids, num_notifications=5000):
    conn = get_connection()
    
    # 알림 타입
    notification_types = ['INFO', 'SUCCESS', 'WARNING', 'ERROR', 'SYSTEM']
    
    # 알림 상태
    status_options = ['READ', 'UNREAD']
    
    # 알림 카테고리별 URL 패턴 정의
    category_url_patterns = {
        # 매칭 알림 관련 URL
        "매칭 요청": lambda sender_id, receiver_id: f"/matching/requests/{sender_id}-to-{receiver_id}",
        "매칭 수락": lambda sender_id, receiver_id: f"/matching/accepted/{sender_id}-{receiver_id}",
        "매칭 거절": lambda sender_id, receiver_id: f"/matching/rejected/{sender_id}-{receiver_id}",
        "매칭 취소": lambda sender_id, receiver_id: f"/matching/cancelled/{sender_id}-{receiver_id}",
        "매칭 완료": lambda sender_id, receiver_id: f"/matching/completed/{sender_id}-{receiver_id}",
        
        # 시스템 알림 관련 URL
        "계정 정보": lambda sender_id, receiver_id: f"/account/settings/{receiver_id}",
        "보안 알림": lambda sender_id, receiver_id: f"/security/alerts/{receiver_id}",
        "업데이트 안내": lambda sender_id, receiver_id: f"/updates/news/{random.randint(1000, 9999)}",
        
        # 활동 알림 관련 URL
        "팔로우": lambda sender_id, receiver_id: f"/profile/{sender_id}",
        "댓글": lambda sender_id, receiver_id: f"/posts/{random.randint(1000, 9999)}#comment-{random.randint(100, 999)}",
        "좋아요": lambda sender_id, receiver_id: f"/posts/{random.randint(1000, 9999)}",
        "멘션": lambda sender_id, receiver_id: f"/posts/{random.randint(1000, 9999)}#mention-{receiver_id}",
        
        # 공지사항 관련 URL
        "서비스 공지": lambda sender_id, receiver_id: f"/notices/service/{random.randint(1000, 9999)}",
        "이벤트 안내": lambda sender_id, receiver_id: f"/events/{random.randint(100, 999)}"
    }
    
    try:
        # 먼저 알림 카테고리 이름과 ID 매핑을 가져옴
        category_name_id_map = {}
        with conn.cursor() as cursor:
            cursor.execute("SELECT notification_category_id, name FROM notification_category")
            for category_id, name in cursor.fetchall():
                category_name_id_map[name] = category_id
        
        # 알림 삽입
        with conn.cursor() as cursor:
            sql = """
                INSERT INTO notification 
                (receiver_id, sender_id, notification_category_id, title, content, type, url, status, created_at, updated_at)
                VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s, %s)
            """
            
            for i in range(num_notifications):
                receiver_id = random.choice(member_ids)
                
                # 발신자는 다른 회원 또는 시스템(ID 1)
                if random.random() < 0.8:  # 80%는 다른 회원이 발신자
                    potential_senders = [mid for mid in member_ids if mid != receiver_id]
                    sender_id = random.choice(potential_senders)
                else:  # 20%는 시스템 알림
                    sender_id = 1  # 관리자 또는 시스템 ID
                
                # 랜덤으로 카테고리 이름 선택
                category_name = random.choice(list(category_name_id_map.keys()))
                category_id = category_name_id_map[category_name]
                
                # 카테고리에 맞는 제목과 내용 생성
                if "매칭" in category_name:
                    title = f"{category_name}: 새로운 매칭 정보가 있습니다"
                    content = f"회원 ID {sender_id}님으로부터의 매칭 관련 알림입니다."
                elif "시스템" in category_name or "계정" in category_name or "보안" in category_name:
                    title = f"{category_name}: 중요 안내사항"
                    content = f"회원님의 계정 관련 중요 안내사항이 있습니다. 확인해주세요."
                elif "팔로우" in category_name:
                    title = "새로운 팔로워"
                    content = f"회원 ID {sender_id}님이 회원님을 팔로우하기 시작했습니다."
                elif "댓글" in category_name:
                    title = "새로운 댓글"
                    content = f"회원 ID {sender_id}님이 회원님의 게시물에 댓글을 남겼습니다."
                elif "좋아요" in category_name:
                    title = "새로운 좋아요"
                    content = f"회원 ID {sender_id}님이 회원님의 게시물을 좋아합니다."
                elif "공지" in category_name or "이벤트" in category_name:
                    title = f"[공지] {category_name}"
                    content = f"새로운 {category_name}이 등록되었습니다. 지금 확인해보세요!"
                else:
                    title = f"새로운 {category_name}"
                    content = f"회원 ID {sender_id}님으로부터의 알림입니다."
                
                notification_type = random.choice(notification_types)
                
                # 카테고리에 맞는 URL 생성
                url = None
                for pattern_key, url_generator in category_url_patterns.items():
                    if pattern_key in category_name:
                        url = f"https://example.com{url_generator(sender_id, receiver_id)}"
                        break
                
                # 찾지 못한 경우 기본 URL 사용
                if url is None:
                    url = f"https://example.com/notifications/{random.randint(10000, 99999)}"
                
                status = random.choice(status_options)
                
                created_at = fake.date_time_between(start_date='-6m', end_date='-1h')
                
                if status == 'READ':
                    updated_at = fake.date_time_between(start_date=created_at, end_date='now')
                else:
                    updated_at = None
                
                cursor.execute(sql, (
                    receiver_id, sender_id, category_id, title, content, 
                    notification_type, url, status, created_at, updated_at
                ))
                
                if (i + 1) % 1000 == 0:
                    conn.commit()
                    print(f"{i + 1}개 알림 데이터 삽입됨.")
            
            conn.commit()
            print(f"총 {num_notifications}개의 알림 데이터 삽입 완료!")
            
    finally:
        conn.close()

def insert_notification_reservations(member_ids, num_reservations=1000):
    conn = get_connection()
    
    try:
        with conn.cursor() as cursor:
            sql = """
                INSERT INTO notification_reservation 
                (receiver_id, content, created_at, deleted_at)
                VALUES (%s, %s, %s, %s)
            """
            
            for i in range(num_reservations):
                receiver_id = random.choice(member_ids)
                content = fake.paragraph(nb_sentences=1)[:250]  # 내용 길이 제한
                
                created_at = fake.date_time_between(start_date='-3m', end_date='-1d')
                
                # 약 20%는 삭제된 예약
                if random.random() < 0.2:
                    deleted_at = fake.date_time_between(start_date=created_at, end_date='now')
                else:
                    deleted_at = None
                
                cursor.execute(sql, (receiver_id, content, created_at, deleted_at))
                
                if (i + 1) % 200 == 0:
                    conn.commit()
                    print(f"{i + 1}개 알림 예약 데이터 삽입됨.")
            
            conn.commit()
            print(f"총 {num_reservations}개의 알림 예약 데이터 삽입 완료!")
            
    finally:
        conn.close()

def insert_project_funcs():
    conn = get_connection()
    project_func_ids = {}
    
    # 상위 프로젝트 기능
    parent_funcs = [
        {"id": 1000, "name": "프로젝트 관리", "code": "PRJ", "level": 1, "parent_id": 0},
        {"id": 2000, "name": "개발", "code": "DEV", "level": 1, "parent_id": 0},
        {"id": 3000, "name": "디자인", "code": "DSN", "level": 1, "parent_id": 0},
        {"id": 4000, "name": "테스트", "code": "TST", "level": 1, "parent_id": 0},
        {"id": 5000, "name": "배포", "code": "DPL", "level": 1, "parent_id": 0}
    ]
    
    # 하위 프로젝트 기능
    child_funcs = {
        1000: [
            {"id": 1001, "name": "요구사항 분석", "code": "REQ", "level": 2, "parent_id": 1000},
            {"id": 1002, "name": "일정 관리", "code": "SCH", "level": 2, "parent_id": 1000},
            {"id": 1003, "name": "리소스 할당", "code": "RSC", "level": 2, "parent_id": 1000}
        ],
        2000: [
            {"id": 2001, "name": "프론트엔드 개발", "code": "FRD", "level": 2, "parent_id": 2000},
            {"id": 2002, "name": "백엔드 개발", "code": "BKD", "level": 2, "parent_id": 2000},
            {"id": 2003, "name": "데이터베이스 설계", "code": "DBS", "level": 2, "parent_id": 2000},
            {"id": 2004, "name": "API 개발", "code": "API", "level": 2, "parent_id": 2000}
        ],
        3000: [
            {"id": 3001, "name": "UI 디자인", "code": "UID", "level": 2, "parent_id": 3000},
            {"id": 3002, "name": "UX 디자인", "code": "UXD", "level": 2, "parent_id": 3000},
            {"id": 3003, "name": "그래픽 디자인", "code": "GRD", "level": 2, "parent_id": 3000}
        ],
        4000: [
            {"id": 4001, "name": "단위 테스트", "code": "UNT", "level": 2, "parent_id": 4000},
            {"id": 4002, "name": "통합 테스트", "code": "INT", "level": 2, "parent_id": 4000},
            {"id": 4003, "name": "성능 테스트", "code": "PFT", "level": 2, "parent_id": 4000},
            {"id": 4004, "name": "보안 테스트", "code": "SCT", "level": 2, "parent_id": 4000}
        ],
        5000: [
            {"id": 5001, "name": "CI/CD", "code": "CIC", "level": 2, "parent_id": 5000},
            {"id": 5002, "name": "모니터링", "code": "MON", "level": 2, "parent_id": 5000},
            {"id": 5003, "name": "유지보수", "code": "MNT", "level": 2, "parent_id": 5000}
        ]
    }
    
    try:
        with conn.cursor() as cursor:
            # 부모 프로젝트 기능 삽입
            parent_sql = """
                INSERT INTO project_func
                (project_func_id, name, code, level, parent_id)
                VALUES (%s, %s, %s, %s, %s)
            """
            
            for parent in parent_funcs:
                try:
                    cursor.execute(parent_sql, (
                        parent["id"], parent["name"], parent["code"], 
                        parent["level"], parent["parent_id"]
                    ))
                    project_func_ids[parent["id"]] = []
                except pymysql.err.IntegrityError:
                    # 이미 존재하는 경우 무시
                    print(f"프로젝트 기능 ID {parent['id']}는 이미 존재함")
                    project_func_ids[parent["id"]] = []
                    continue
            
            conn.commit()
            
            # 자식 프로젝트 기능 삽입
            for parent_id, children in child_funcs.items():
                for child in children:
                    try:
                        cursor.execute(parent_sql, (
                            child["id"], child["name"], child["code"], 
                            child["level"], child["parent_id"]
                        ))
                        project_func_ids[parent_id].append(child["id"])
                    except pymysql.err.IntegrityError:
                        # 이미 존재하는 경우 무시
                        print(f"프로젝트 기능 ID {child['id']}는 이미 존재함")
                        project_func_ids[parent_id].append(child["id"])
                        continue
            
            conn.commit()
            
            # 프로젝트 기능 개수 계산
            total_funcs = len(project_func_ids) + sum(len(children) for children in project_func_ids.values())
            print(f"총 {total_funcs}개의 프로젝트 기능 데이터 삽입 완료!")
            
    finally:
        conn.close()
        
    return project_func_ids

def insert_comments(member_ids, project_func_ids, num_comments=3000):
    conn = get_connection()
    comment_ids = []
    
    # 모든 프로젝트 기능 ID 평탄화
    all_func_ids = []
    for parent_id, child_ids in project_func_ids.items():
        all_func_ids.append(parent_id)
        all_func_ids.extend(child_ids)
    
    try:
        with conn.cursor() as cursor:
            sql = """
                INSERT INTO comment
                (member_id, project_func_id, created_at, updated_at, deleted, description, level, parent_comment_id)
                VALUES (%s, %s, %s, %s, %s, %s, %s, %s)
            """
            
            # 먼저 부모 댓글 생성 (약 70%)
            parent_count = int(num_comments * 0.7)
            
            for i in range(parent_count):
                member_id = random.choice(member_ids)
                project_func_id = random.choice(all_func_ids)
                created_at = fake.date_time_between(start_date='-1y', end_date='-1d')
                updated_at = fake.date_time_between(start_date=created_at, end_date='now')
                deleted = 'FALSE'
                description = fake.paragraph(nb_sentences=2)[:250]  # 내용 길이 제한
                level = 1  # 부모 댓글은 레벨 1
                parent_comment_id = None
                
                cursor.execute(sql, (
                    member_id, project_func_id, created_at, updated_at,
                    deleted, description, level, parent_comment_id
                ))
                comment_ids.append(cursor.lastrowid)
                
                if (i + 1) % 1000 == 0:
                    conn.commit()
                    print(f"{i + 1}개 부모 댓글 데이터 삽입됨.")
            
            conn.commit()
            
            # 자식 댓글 생성 (약 30%)
            child_count = num_comments - parent_count
            
            for i in range(child_count):
                member_id = random.choice(member_ids)
                # 부모 댓글의 project_func_id를 가져오기
                parent_comment_id = random.choice(comment_ids)
                
                # 부모 댓글의 project_func_id 조회
                cursor.execute("SELECT project_func_id FROM comment WHERE comment_id = %s", (parent_comment_id,))
                project_func_id = cursor.fetchone()[0]
                
                created_at = fake.date_time_between(start_date='-1y', end_date='-1d')
                updated_at = fake.date_time_between(start_date=created_at, end_date='now')
                deleted = 'FALSE'
                description = fake.paragraph(nb_sentences=1)[:250]  # 내용 길이 제한
                level = 2  # 자식 댓글은 레벨 2
                
                cursor.execute(sql, (
                    member_id, project_func_id, created_at, updated_at,
                    deleted, description, level, parent_comment_id
                ))
                
                if (i + 1) % 500 == 0:
                    conn.commit()
                    print(f"{i + 1}개 자식 댓글 데이터 삽입됨.")
            
            conn.commit()
            print(f"총 {num_comments}개의 댓글 데이터 삽입 완료!")
            
    finally:
        conn.close()
        
    return comment_ids

def insert_member_ratings(member_ids, project_func_ids, num_ratings=5000):
    conn = get_connection()
    
    # 모든 프로젝트 기능 ID 평탄화
    all_func_ids = []
    for parent_id, child_ids in project_func_ids.items():
        all_func_ids.append(parent_id)
        all_func_ids.extend(child_ids)
    
    try:
        with conn.cursor() as cursor:
            sql = """
                INSERT INTO member_rating
                (member_id, project_func_id, rate)
                VALUES (%s, %s, %s)
            """
            
            # 중복 방지를 위한 집합
            processed_pairs = set()
            count = 0
            
            while count < num_ratings:
                member_id = random.choice(member_ids)
                project_func_id = random.choice(all_func_ids)
                
                # 중복 체크
                pair = (member_id, project_func_id)
                if pair in processed_pairs:
                    continue
                
                processed_pairs.add(pair)
                
                # 평점은 1.0에서 5.0 사이, 소수점 한 자리
                rate = round(random.uniform(1.0, 5.0), 1)
                
                cursor.execute(sql, (member_id, project_func_id, rate))
                count += 1
                
                if count % 1000 == 0:
                    conn.commit()
                    print(f"{count}개 회원 평점 데이터 삽입됨.")
            
            conn.commit()
            print(f"총 {count}개의 회원 평점 데이터 삽입 완료!")
            
    finally:
        conn.close()

def insert_member_points(member_ids, project_func_ids, num_points=8000):
    conn = get_connection()
    
    # 모든 프로젝트 기능 ID 평탄화
    all_func_ids = []
    for parent_id, child_ids in project_func_ids.items():
        all_func_ids.append(parent_id)
        all_func_ids.extend(child_ids)
    
    try:
        with conn.cursor() as cursor:
            sql = """
                INSERT INTO member_point
                (member_id, project_func_id, current_point, updated_at)
                VALUES (%s, %s, %s, %s)
            """
            
            # 중복 방지를 위한 집합
            processed_pairs = set()
            count = 0
            
            while count < num_points:
                member_id = random.choice(member_ids)
                project_func_id = random.choice(all_func_ids)
                
                # 중복 체크
                pair = (member_id, project_func_id)
                if pair in processed_pairs:
                    continue
                
                processed_pairs.add(pair)
                
                # 포인트는 0에서 10000 사이
                current_point = random.randint(0, 10000)
                updated_at = fake.date_time_between(start_date='-1y', end_date='now')
                
                cursor.execute(sql, (member_id, project_func_id, current_point, updated_at))
                count += 1
                
                if count % 1000 == 0:
                    conn.commit()
                    print(f"{count}개 회원 포인트 데이터 삽입됨.")
            
            conn.commit()
            print(f"총 {count}개의 회원 포인트 데이터 삽입 완료!")
            
    finally:
        conn.close()

def insert_experiences(member_ids, project_func_ids, num_experiences=10000):
    conn = get_connection()
    
    # 모든 프로젝트 기능 ID 평탄화
    all_func_ids = []
    for parent_id, child_ids in project_func_ids.items():
        all_func_ids.append(parent_id)
        all_func_ids.extend(child_ids)
    
    try:
        with conn.cursor() as cursor:
            sql = """
                INSERT INTO experience
                (member_id, project_func_id, amount, created_at)
                VALUES (%s, %s, %s, %s)
            """
            
            for i in range(num_experiences):
                member_id = random.choice(member_ids)
                
                # 약 10%는 project_func_id가 NULL
                if random.random() < 0.1:
                    project_func_id = None
                else:
                    project_func_id = random.choice(all_func_ids)
                
                # 경험치 금액은 10에서 1000 사이
                amount = random.randint(10, 1000)
                created_at = fake.date_time_between(start_date='-1y', end_date='now')
                
                cursor.execute(sql, (member_id, project_func_id, amount, created_at))
                
                if (i + 1) % 1000 == 0:
                    conn.commit()
                    print(f"{i + 1}개 경험치 데이터 삽입됨.")
            
            conn.commit()
            print(f"총 {num_experiences}개의 경험치 데이터 삽입 완료!")
            
    finally:
        conn.close()

def insert_retrospects(member_ids, project_func_ids, num_retrospects=2000):
    conn = get_connection()
    retrospect_ids = []
    
    # 모든 프로젝트 기능 ID 평탄화
    all_func_ids = []
    for parent_id, child_ids in project_func_ids.items():
        all_func_ids.append(parent_id)
        all_func_ids.extend(child_ids)
    
    try:
        with conn.cursor() as cursor:
            # 부모 회고 생성 (약 70%)
            parent_sql = """
                INSERT INTO retrospect
                (project_func_id, deleted, created_at, updated_at, description, parent_id)
                VALUES (%s, %s, %s, %s, %s, %s)
            """
            
            # 먼저 부모 회고 생성
            parent_count = int(num_retrospects * 0.7)
            
            for i in range(parent_count):
                project_func_id = random.choice(all_func_ids)
                deleted = 'FALSE'
                created_at = fake.date_time_between(start_date='-1y', end_date='-1d')
                updated_at = fake.date_time_between(start_date=created_at, end_date='now')
                description = fake.paragraph(nb_sentences=3)[:250]  # 내용 길이 제한
                
                # 부모 회고의 parent_id는 자기 자신 (최초 삽입 시 ID를 모르므로 0으로 설정)
                parent_id = 0
                
                cursor.execute(parent_sql, (
                    project_func_id, deleted, created_at, updated_at, description, parent_id
                ))
                retrospect_id = cursor.lastrowid
                retrospect_ids.append(retrospect_id)
                
                # 부모 ID 업데이트
                cursor.execute("""
                    UPDATE retrospect
                    SET parent_id = %s
                    WHERE retrospect_id = %s
                """, (retrospect_id, retrospect_id))
                
                if (i + 1) % 500 == 0:
                    conn.commit()
                    print(f"{i + 1}개 부모 회고 데이터 삽입됨.")
            
            conn.commit()
            
            # 자식 회고 생성 (약 30%)
            child_count = num_retrospects - parent_count
            
            for i in range(child_count):
                # 부모 회고 중 하나를 선택
                parent_retrospect_id = random.choice(retrospect_ids)
                
                # 부모 회고의 project_func_id를 가져옴
                cursor.execute("SELECT project_func_id FROM retrospect WHERE retrospect_id = %s", 
                              (parent_retrospect_id,))
                project_func_id = cursor.fetchone()[0]
                
                deleted = 'FALSE'
                created_at = fake.date_time_between(start_date='-1y', end_date='-1d')
                updated_at = fake.date_time_between(start_date=created_at, end_date='now')
                description = fake.paragraph(nb_sentences=2)[:250]  # 내용 길이 제한
                
                cursor.execute(parent_sql, (
                    project_func_id, deleted, created_at, updated_at, description, parent_retrospect_id
                ))
                
                if (i + 1) % 300 == 0:
                    conn.commit()
                    print(f"{i + 1}개 자식 회고 데이터 삽입됨.")
            
            conn.commit()
            print(f"총 {num_retrospects}개의 회고 데이터 삽입 완료!")
            
    finally:
        conn.close()
        
    return retrospect_ids

def insert_follows(member_ids, num_follows=5000):
    conn = get_connection()
    
    try:
        with conn.cursor() as cursor:
            sql = """
                INSERT INTO follow
                (follower_id, followed_id, created_at)
                VALUES (%s, %s, %s)
            """
            
            # 중복 방지를 위한 집합
            processed_pairs = set()
            count = 0
            
            while count < num_follows:
                follower_id = random.choice(member_ids)
                
                # 자기 자신이 아닌 다른 멤버를 팔로우 대상으로 선택
                potential_followed = [mid for mid in member_ids if mid != follower_id]
                followed_id = random.choice(potential_followed)
                
                # 중복 체크
                pair = (follower_id, followed_id)
                if pair in processed_pairs:
                    continue
                
                processed_pairs.add(pair)
                
                created_at = fake.date_time_between(start_date='-1y', end_date='now')
                
                try:
                    cursor.execute(sql, (follower_id, followed_id, created_at))
                    count += 1
                except pymysql.err.IntegrityError:
                    # 중복 키 무시
                    continue
                
                if count % 1000 == 0:
                    conn.commit()
                    print(f"{count}개 팔로우 데이터 삽입됨.")
            
            conn.commit()
            print(f"총 {count}개의 팔로우 데이터 삽입 완료!")
            
    finally:
        conn.close()

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
                except pymysql.err.IntegrityError:
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
                    except pymysql.err.IntegrityError:
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

def main():
    print("데이터 삽입을 시작합니다...")
    # 기존 데이터 삭제
    truncate_tables()
    
    # 멤버 데이터 삽입
    member_ids = insert_members(10000)
    
    # 이미지 데이터 삽입
    image_ids = insert_images(5000)
    insert_resized_images(image_ids)
    
    # 멤버 프로필 데이터 삽입
    member_profile_ids = insert_member_profiles(member_ids, image_ids)
    
    # 회원 상세정보 및 블랙리스트 데이터 삽입
    insert_member_details(member_ids)
    insert_blacklist(member_ids)
    
    # 매칭 필드 및 스킬 카테고리 데이터 삽입
    insert_matching_fields()
    skill_category_ids = insert_skill_categories()
    
    # 매칭 템플릿 관련 데이터 삽입
    conn = get_connection()
    matching_field_ids = []
    try:
        with conn.cursor() as cursor:
            cursor.execute("SELECT matching_field_id FROM matching_field")
            matching_field_ids = [row[0] for row in cursor.fetchall()]
    finally:
        conn.close()
    
    template_ids = insert_matching_templates()
    insert_matching_template_details(template_ids, matching_field_ids, skill_category_ids)
    matching_request_ids = insert_matching_requests(member_ids, template_ids)
    insert_matching_request_partners(matching_request_ids, member_ids)
    
    # 알림 관련 데이터 삽입
    notification_category_ids = insert_notification_categories()
    insert_notification_settings(member_ids, notification_category_ids)
    insert_notifications(member_ids, notification_category_ids)
    insert_notification_reservations(member_ids)
    
    # 프로젝트 기능 및 관련 데이터 삽입
    project_func_ids = insert_project_funcs()
    insert_comments(member_ids, project_func_ids)
    insert_member_ratings(member_ids, project_func_ids)
    insert_member_points(member_ids, project_func_ids)
    insert_experiences(member_ids, project_func_ids)
    
    # 회고 데이터 삽입
    insert_retrospects(member_ids, project_func_ids)
    
    # 팔로우 데이터 삽입
    insert_follows(member_ids)
    
    # 스터디 관련 데이터 삽입
    study_space_ids = insert_study_spaces()
    daily_study_ids = insert_daily_study_contents(member_ids, study_space_ids)
    insert_attendances(daily_study_ids)
    
    # 대시보드 관련 데이터 삽입
    dashboard_category_ids = insert_dashboard_categories()
    insert_study_dashboards(member_ids, dashboard_category_ids)
    
    # 소셜 미디어 관련 데이터 삽입
    social_media_type_ids = insert_social_media_types(image_ids)
    insert_social_media(member_profile_ids, social_media_type_ids)
    
    # 기술 스택 관련 데이터 삽입
    tech_stack_ids = insert_tech_stacks(image_ids)
    insert_tech_stack_refs(member_profile_ids, tech_stack_ids)
    
    print("모든 데이터 삽입이 완료되었습니다!")
    
    # 각 테이블별 데이터 수 출력
    print_table_counts()

if __name__ == "__main__":
    main()
