from .common import get_connection, fake
import random

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