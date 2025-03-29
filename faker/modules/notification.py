from .common import get_connection, fake
import random
import datetime

def insert_notification_categories():
    conn = get_connection()
    
    categories = [
        {"name": "사용자", "description": "사용자 관련 알림", "parent_id": None},
        {"name": "팔로우", "description": "팔로우 관련 알림", "parent_id": 1},
        {"name": "프로젝트", "description": "프로젝트 관련 알림", "parent_id": None},
        {"name": "댓글", "description": "댓글 관련 알림", "parent_id": 3},
        {"name": "좋아요", "description": "좋아요 관련 알림", "parent_id": 3},
        {"name": "매칭", "description": "매칭 관련 알림", "parent_id": None},
        {"name": "매칭 요청", "description": "매칭 요청 알림", "parent_id": 6},
        {"name": "매칭 수락", "description": "매칭 수락 알림", "parent_id": 6},
        {"name": "매칭 거절", "description": "매칭 거절 알림", "parent_id": 6},
        {"name": "스터디", "description": "스터디 관련 알림", "parent_id": None},
        {"name": "스터디 초대", "description": "스터디 초대 알림", "parent_id": 10},
        {"name": "스터디 수락", "description": "스터디 수락 알림", "parent_id": 10},
        {"name": "스터디 거절", "description": "스터디 거절 알림", "parent_id": 10}
    ]
    
    try:
        with conn.cursor() as cursor:
            sql = """
                INSERT INTO notification_category 
                (id, name, description, parent_id, created_at, updated_at)
                VALUES (%s, %s, %s, %s, %s, %s)
            """

            for i, category in enumerate(categories, 1):
                name = category["name"]
                description = category["description"]
                parent_id = category["parent_id"]
                created_at = fake.date_time_between(start_date='-2y', end_date='now')
                updated_at = created_at

                cursor.execute(sql, (i, name, description, parent_id, created_at, updated_at))

            conn.commit()
            print(f"총 {len(categories)}개의 알림 카테고리 삽입 완료!")
            
    finally:
        conn.close()
    
    # 카테고리와 그들의 ID를 반환
    return [(i+1, category["name"], category["parent_id"]) for i, category in enumerate(categories)]

def insert_notification_settings(member_ids):
    conn = get_connection()
    
    try:
        with conn.cursor() as cursor:
            sql = """
                INSERT INTO notification_setting 
                (member_id, push, email, created_at, updated_at)
                VALUES (%s, %s, %s, %s, %s)
            """

            for i, member_id in enumerate(member_ids):
                push = random.choice(['T', 'F'])
                email = random.choice(['T', 'F'])
                created_at = fake.date_time_between(start_date='-2y', end_date='now')
                updated_at = created_at

                cursor.execute(sql, (member_id, push, email, created_at, updated_at))

                if (i + 1) % 1000 == 0:
                    conn.commit()
                    print(f"{i + 1}개 알림 설정 데이터 삽입됨.")

            conn.commit()
            print(f"총 {len(member_ids)}개의 알림 설정 데이터 삽입 완료!")
            
    finally:
        conn.close()

def insert_notifications(member_ids, notification_categories, project_ids=None, project_func_ids=None, study_ids=None, num_notifications=5000):
    conn = get_connection()
    notification_ids = []
    
    # 카테고리 ID별로 그룹화
    category_by_parent = {}
    for cat_id, name, parent_id in notification_categories:
        if parent_id not in category_by_parent:
            category_by_parent[parent_id] = []
        category_by_parent[parent_id].append((cat_id, name))

    # 상위 카테고리 IDs (parent_id가 None인 카테고리)
    parent_categories = [cat_id for cat_id, name, parent_id in notification_categories if parent_id is None]
    
    try:
        with conn.cursor() as cursor:
            sql = """
                INSERT INTO notification 
                (member_id, notification_category_id, title, content, url, is_read, created_at, updated_at)
                VALUES (%s, %s, %s, %s, %s, %s, %s, %s)
            """

            for i in range(num_notifications):
                member_id = random.choice(member_ids)
                
                # 상위 카테고리 선택
                parent_category_id = random.choice(parent_categories)
                
                # 해당 상위 카테고리의 하위 카테고리 중 선택
                child_categories = category_by_parent.get(parent_category_id, [])
                
                # 하위 카테고리가 있으면 그 중에서 선택, 없으면 상위 카테고리 사용
                if child_categories:
                    notification_category_id, category_name = random.choice(child_categories)
                else:
                    notification_category_id = parent_category_id
                    category_name = next((name for cat_id, name, _ in notification_categories if cat_id == parent_category_id), "알림")
                
                # 카테고리별 맞춤 제목과 내용 생성
                title, content, url = generate_notification_content(
                    notification_category_id, 
                    category_name, 
                    member_ids, 
                    project_ids, 
                    project_func_ids, 
                    study_ids
                )
                
                is_read = random.choice(['T', 'F'])
                created_at = fake.date_time_between(start_date='-1y', end_date='now')
                updated_at = created_at

                cursor.execute(sql, (member_id, notification_category_id, title, content, url, is_read, created_at, updated_at))
                notification_ids.append(cursor.lastrowid)

                if (i + 1) % 1000 == 0:
                    conn.commit()
                    print(f"{i + 1}개 알림 데이터 삽입됨.")

            conn.commit()
            print(f"총 {num_notifications}개의 알림 데이터 삽입 완료!")
            
    finally:
        conn.close()
        
    return notification_ids

def generate_notification_content(category_id, category_name, member_ids, project_ids=None, project_func_ids=None, study_ids=None):
    # 기본값
    if project_ids is None:
        project_ids = [random.randint(1, 100) for _ in range(20)]
    if project_func_ids is None:
        project_func_ids = [random.randint(1, 50) for _ in range(20)]
    if study_ids is None:
        study_ids = [random.randint(1, 30) for _ in range(10)]
    
    # 카테고리별 맞춤 내용 생성
    if "팔로우" in category_name:
        other_member_id = random.choice(member_ids)
        title = f"새 팔로워가 있습니다"
        content = f"사용자 ID:{other_member_id}님이 회원님을 팔로우했습니다."
        url = f"/members/{other_member_id}"
    
    elif "댓글" in category_name:
        project_id = random.choice(project_ids)
        project_func_id = random.choice(project_func_ids)
        other_member_id = random.choice(member_ids)
        title = "새 댓글이 달렸습니다"
        content = f"회원님의 프로젝트에 ID:{other_member_id}님이 댓글을 남겼습니다: '{fake.sentence()}'"
        url = f"/projects/{project_id}/functions/{project_func_id}"
    
    elif "좋아요" in category_name:
        project_id = random.choice(project_ids)
        other_member_id = random.choice(member_ids)
        title = "누군가 회원님의 프로젝트를 좋아합니다"
        content = f"ID:{other_member_id}님이 회원님의 프로젝트에 좋아요를 눌렀습니다."
        url = f"/projects/{project_id}"
    
    elif "매칭 요청" in category_name:
        other_member_id = random.choice(member_ids)
        title = "새로운 매칭 요청이 있습니다"
        content = f"ID:{other_member_id}님으로부터 새로운 매칭 요청이 있습니다."
        url = f"/matching/requests"
    
    elif "매칭 수락" in category_name:
        other_member_id = random.choice(member_ids)
        title = "매칭 요청이 수락되었습니다"
        content = f"ID:{other_member_id}님이 회원님의 매칭 요청을 수락했습니다."
        url = f"/matching/accepted"
    
    elif "매칭 거절" in category_name:
        other_member_id = random.choice(member_ids)
        title = "매칭 요청이 거절되었습니다"
        content = f"ID:{other_member_id}님이 회원님의 매칭 요청을 거절했습니다."
        url = f"/matching/rejected"
    
    elif "스터디 초대" in category_name:
        study_id = random.choice(study_ids)
        other_member_id = random.choice(member_ids)
        title = "스터디 초대가 도착했습니다"
        content = f"ID:{other_member_id}님이 회원님을 스터디에 초대했습니다."
        url = f"/studies/{study_id}/invitations"
    
    elif "스터디 수락" in category_name:
        study_id = random.choice(study_ids)
        other_member_id = random.choice(member_ids)
        title = "스터디 초대가 수락되었습니다"
        content = f"ID:{other_member_id}님이 회원님의 스터디 초대를 수락했습니다."
        url = f"/studies/{study_id}/members"
    
    elif "스터디 거절" in category_name:
        study_id = random.choice(study_ids)
        other_member_id = random.choice(member_ids)
        title = "스터디 초대가 거절되었습니다"
        content = f"ID:{other_member_id}님이 회원님의 스터디 초대를 거절했습니다."
        url = f"/studies/{study_id}/invitations"
    
    else:
        title = f"{category_name} 관련 알림"
        content = fake.sentence()
        url = "/"
    
    return title, content, url

def insert_notification_reservations(member_ids, notification_category_ids, num_reservations=100):
    conn = get_connection()
    
    try:
        with conn.cursor() as cursor:
            sql = """
                INSERT INTO notification_reservation 
                (member_id, notification_category_id, title, content, url, reserved_at, created_at, updated_at)
                VALUES (%s, %s, %s, %s, %s, %s, %s, %s)
            """

            for i in range(num_reservations):
                member_id = random.choice(member_ids)
                notification_category_id = random.choice(notification_category_ids)
                
                title = f"예약된 알림 #{i+1}"
                content = fake.sentence()
                url = f"/{random.choice(['projects', 'studies', 'members'])}/{random.randint(1, 100)}"
                
                # 현재 시간부터 30일 이내의 미래 시간
                reserved_at = fake.date_time_between(start_date='now', end_date='+30d')
                created_at = fake.date_time_between(start_date='-7d', end_date='now')
                updated_at = created_at

                cursor.execute(sql, (member_id, notification_category_id, title, content, url, reserved_at, created_at, updated_at))

                if (i + 1) % 20 == 0:
                    conn.commit()
                    print(f"{i + 1}개 알림 예약 데이터 삽입됨.")

            conn.commit()
            print(f"총 {num_reservations}개의 알림 예약 데이터 삽입 완료!")
            
    finally:
        conn.close() 