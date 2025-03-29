from .common import get_connection, fake
import random
import uuid

def insert_social_media_types(image_ids, num_types=10):
    conn = get_connection()
    social_media_type_ids = []
    
    # 소셜 미디어 타입 목록
    social_media_types = [
        {"name": "Facebook", "domain": "facebook.com"},
        {"name": "Twitter", "domain": "twitter.com"},
        {"name": "Instagram", "domain": "instagram.com"},
        {"name": "LinkedIn", "domain": "linkedin.com"},
        {"name": "GitHub", "domain": "github.com"},
        {"name": "Medium", "domain": "medium.com"},
        {"name": "YouTube", "domain": "youtube.com"},
        {"name": "Dribbble", "domain": "dribbble.com"},
        {"name": "Behance", "domain": "behance.net"},
        {"name": "Personal Blog", "domain": "blog.com"}
    ]
    
    try:
        with conn.cursor() as cursor:
            for i, type_info in enumerate(social_media_types[:num_types]):
                # 랜덤 이미지 ID 선택
                image_id = random.choice(image_ids) if random.random() < 0.8 else None
                
                sql = """
                    INSERT INTO social_media_type 
                    (name, domain, image_id, created_at, updated_at)
                    VALUES (%s, %s, %s, %s, %s)
                """
                
                created_at = fake.date_time_between(start_date='-2y', end_date='now')
                updated_at = created_at
                
                cursor.execute(sql, (
                    type_info["name"],
                    type_info["domain"],
                    image_id,
                    created_at,
                    updated_at
                ))
                
                social_media_type_ids.append(cursor.lastrowid)
            
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
                (member_profile_id, social_media_type_id, url, created_at, updated_at)
                VALUES (%s, %s, %s, %s, %s)
            """
            
            # 중복 체크를 위한 set
            processed_pairs = set()
            count = 0
            
            while count < num_records:
                member_profile_id = random.choice(member_profile_ids)
                social_media_type_id = random.choice(social_media_type_ids)
                
                # 중복 체크
                pair = (member_profile_id, social_media_type_id)
                if pair in processed_pairs:
                    continue
                
                processed_pairs.add(pair)
                
                # 소셜 미디어 타입 정보 가져오기
                cursor.execute("SELECT domain FROM social_media_type WHERE social_media_type_id = %s", 
                              (social_media_type_id,))
                domain = cursor.fetchone()[0]
                
                # URL 생성
                username = fake.user_name()
                url = f"https://www.{domain}/{username}"
                
                created_at = fake.date_time_between(start_date='-1y', end_date='now')
                updated_at = created_at
                
                cursor.execute(sql, (member_profile_id, social_media_type_id, url, created_at, updated_at))
                count += 1
                
                if count % 500 == 0:
                    conn.commit()
                    print(f"{count}개 소셜 미디어 데이터 삽입됨.")
            
            conn.commit()
            print(f"총 {count}개의 소셜 미디어 데이터 삽입 완료!")
            
    finally:
        conn.close()

def insert_tech_stacks(image_ids, num_parent_stacks=10, num_child_stacks_per_parent=5):
    conn = get_connection()
    tech_stack_ids = {}
    
    # 상위 기술 스택
    parent_stacks = [
        "프론트엔드",
        "백엔드",
        "데이터베이스",
        "모바일",
        "데브옵스",
        "인공지능/머신러닝",
        "게임 개발",
        "임베디드/IoT",
        "보안",
        "블록체인"
    ]
    
    # 상위 스택별 하위 기술 스택
    child_stacks = {
        "프론트엔드": ["React", "Vue.js", "Angular", "JavaScript", "TypeScript", "HTML/CSS", "Next.js", "Svelte"],
        "백엔드": ["Spring", "Django", "Node.js", "Express", "Laravel", "ASP.NET", "FastAPI", "Ruby on Rails"],
        "데이터베이스": ["MySQL", "PostgreSQL", "MongoDB", "Redis", "Oracle", "SQLite", "Firebase", "Elasticsearch"],
        "모바일": ["Android", "iOS", "React Native", "Flutter", "Kotlin", "Swift", "Xamarin", "Ionic"],
        "데브옵스": ["Docker", "Kubernetes", "Jenkins", "AWS", "GCP", "Azure", "Terraform", "Ansible"],
        "인공지능/머신러닝": ["TensorFlow", "PyTorch", "Scikit-learn", "Keras", "OpenCV", "NLP", "Computer Vision", "MLOps"],
        "게임 개발": ["Unity", "Unreal Engine", "Godot", "C++", "C#", "DirectX", "WebGL", "PhysX"],
        "임베디드/IoT": ["Arduino", "Raspberry Pi", "C/C++", "MQTT", "Embedded Linux", "FreeRTOS", "Bluetooth LE", "ZigBee"],
        "보안": ["암호화", "인증/권한", "네트워크 보안", "취약점 분석", "침투 테스트", "포렌식", "보안 감사", "SIEM"],
        "블록체인": ["Ethereum", "Solidity", "Smart Contracts", "Web3.js", "Hyperledger", "NFT", "DeFi", "dApps"]
    }
    
    try:
        with conn.cursor() as cursor:
            # 상위 스택 먼저 삽입
            parent_sql = """
                INSERT INTO tech_stack 
                (name, image_id, parent_id)
                VALUES (%s, %s, %s)
            """
            
            for i, parent in enumerate(parent_stacks):
                if i < num_parent_stacks:
                    # 이미지 아이디는 랜덤하게 선택 (None일 수도 있음)
                    image_id = random.choice([None] + image_ids) if random.random() < 0.8 and image_ids else None
                    
                    cursor.execute(parent_sql, (parent, image_id, None))
                    parent_id = cursor.lastrowid
                    tech_stack_ids[parent] = {"id": parent_id, "children": []}
            
            conn.commit()
            
            # 하위 스택 삽입
            for parent_name, children in child_stacks.items():
                if parent_name in tech_stack_ids:
                    parent_id = tech_stack_ids[parent_name]["id"]
                    
                    # 선택된 하위 스택 수만큼 삽입
                    selected_children = children[:num_child_stacks_per_parent] if len(children) > num_child_stacks_per_parent else children
                    
                    for child in selected_children:
                        # 이미지 아이디는 랜덤하게 선택 (None일 수도 있음)
                        image_id = random.choice([None] + image_ids) if random.random() < 0.6 and image_ids else None
                        
                        cursor.execute(parent_sql, (child, image_id, parent_id))
                        child_id = cursor.lastrowid
                        tech_stack_ids[parent_name]["children"].append(child_id)
            
            conn.commit()
            
            # 기술 스택 개수 계산
            total_stacks = len(tech_stack_ids) + sum(len(data["children"]) for data in tech_stack_ids.values())
            print(f"총 {total_stacks}개의 기술 스택 데이터 삽입 완료!")
            
    finally:
        conn.close()
        
    return tech_stack_ids

def insert_tech_stack_refs(member_profile_ids, tech_stack_ids, refs_per_member_min=1, refs_per_member_max=5):
    conn = get_connection()
    
    try:
        with conn.cursor() as cursor:
            sql = """
                INSERT INTO tech_stack_ref 
                (member_profile_id, tech_stack_id)
                VALUES (%s, %s)
            """
            
            count = 0
            # 중복 방지를 위한 집합
            processed_pairs = set()
            
            # 모든 기술 스택 ID를 평탄화
            all_tech_stack_ids = []
            for parent_name, data in tech_stack_ids.items():
                all_tech_stack_ids.append(data["id"])  # 상위 스택
                all_tech_stack_ids.extend(data["children"])  # 하위 스택
            
            for member_profile_id in member_profile_ids:
                # 각 회원 프로필마다 1~5개의 기술 스택 참조 생성
                num_refs = random.randint(refs_per_member_min, refs_per_member_max)
                
                if num_refs > 0:
                    # 중복 없이 기술 스택 선택
                    selected_tech_stack_ids = random.sample(all_tech_stack_ids, min(num_refs, len(all_tech_stack_ids)))
                    
                    for tech_stack_id in selected_tech_stack_ids:
                        # 중복 체크
                        pair = (member_profile_id, tech_stack_id)
                        if pair in processed_pairs:
                            continue
                        
                        processed_pairs.add(pair)
                        
                        cursor.execute(sql, (member_profile_id, tech_stack_id))
                        count += 1
                
                if count > 0 and count % 1000 == 0:
                    conn.commit()
                    print(f"{count}개 기술 스택 참조 데이터 삽입됨.")
            
            conn.commit()
            print(f"총 {count}개의 기술 스택 참조 데이터 삽입 완료!")
            
    finally:
        conn.close() 