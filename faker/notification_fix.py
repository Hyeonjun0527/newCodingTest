from modules.common import get_connection, fake
import random

def fix_notifications(member_ids, notification_category_ids, num_notifications=5000):
    """
    notification.py의 insert_notifications 함수에서 발생하는 구문 오류를 수정한 버전입니다.
    """
    conn = get_connection()
    
    # 알림 타입별 제목 및 내용 템플릿
    notification_templates = {
        "공지사항": {
            "titles": [
                "공지: 서비스 이용약관 변경 안내",
                "중요 공지: 개인정보처리방침 업데이트",
                "서비스 점검 안내",
                "신규 기능 출시 안내"
            ],
            "contents": [
                "안녕하세요. 서비스 이용약관이 변경되었습니다. 자세한 내용은 공지사항을 확인해주세요.",
                "개인정보처리방침이 업데이트 되었습니다. 변경 사항을 확인해주세요.",
                "오늘 오전 3시부터 약 2시간 동안 서비스 점검이 예정되어 있습니다.",
                "새로운 기능이 출시되었습니다. 지금 바로 확인해보세요!"
            ],
            "urls": [
                "/notice/terms",
                "/notice/privacy",
                "/notice/maintenance",
                "/notice/new-features"
            ]
        },
        "매칭 요청": {
            "titles": [
                "새로운 매칭 요청이 도착했습니다",
                "{sender_name}님이 매칭을 요청했습니다",
                "매칭 요청: {project_title}"
            ],
            "contents": [
                "{sender_name}님이 프로젝트 '{project_title}'에 대한 매칭을 요청했습니다.",
                "새로운 매칭 요청이 있습니다. 확인해보세요.",
                "{sender_name}님이 회원님의 프로필을 보고 매칭을 요청했습니다."
            ],
            "urls": [
                "/matching/requests/{request_id}",
                "/matching/inbox/{request_id}",
                "/matching/details/{request_id}"
            ]
        },
        "포인트 적립": {
            "titles": [
                "포인트가 적립되었습니다",
                "활동에 대한 보상 포인트 지급",
                "{point_amount} 포인트가 적립되었습니다"
            ],
            "contents": [
                "{activity_name}에 대한 보상으로 {point_amount} 포인트가 적립되었습니다.",
                "축하합니다! {point_amount} 포인트를 획득하셨습니다.",
                "정기 활동 보상으로 {point_amount} 포인트가 지급되었습니다."
            ],
            "urls": [
                "/points/history",
                "/rewards/points",
                "/mypage/points"
            ]
        },
        "계정": {
            "titles": [
                "계정 정보가 변경되었습니다",
                "로그인 알림",
                "프로필 정보 업데이트 안내"
            ],
            "contents": [
                "회원님의 계정 정보가 변경되었습니다. 본인이 변경하지 않았다면 고객센터로 문의해주세요.",
                "새로운 기기에서 로그인이 감지되었습니다. 본인이 아니라면 비밀번호를 변경해주세요.",
                "프로필 정보가 업데이트되었습니다."
            ],
            "urls": [
                "/account/security",
                "/login/history",
                "/profile/edit"
            ]
        }
    }
    
    # 자식 카테고리 정의
    child_categories = {
        "시스템": [
            {"name": "공지사항", "code": "SYS01"},
            {"name": "업데이트", "code": "SYS02"},
            {"name": "서비스 점검", "code": "SYS03"}
        ],
        "매칭": [
            {"name": "매칭 요청", "code": "MTC01"},
            {"name": "매칭 수락", "code": "MTC02"},
            {"name": "매칭 거절", "code": "MTC03"},
            {"name": "매칭 추천", "code": "MTC04"}
        ],
        "멤버십": [
            {"name": "멤버십 혜택", "code": "MEM01"},
            {"name": "포인트 적립", "code": "MEM02"},
            {"name": "포인트 소멸 예정", "code": "MEM03"}
        ],
        "계정": [
            {"name": "비밀번호 변경", "code": "ACC01"},
            {"name": "로그인 알림", "code": "ACC02"},
            {"name": "프로필 업데이트", "code": "ACC03"}
        ]
    }
    
    try:
        with conn.cursor() as cursor:
            sql = """
                INSERT INTO notification 
                (member_id, notification_category_id, title, content, url, sent_at, read_at)
                VALUES (%s, %s, %s, %s, %s, %s, %s)
            """
            
            # 모든 카테고리 아이디를 평탄화
            all_category_ids = []
            category_map = {}  # 카테고리 ID -> 카테고리 이름 매핑
            
            for parent_name, data in notification_category_ids.items():
                # 자식 카테고리 매핑을 위해 해당 부모의 자식 목록을 가져옴
                parent_children = child_categories.get(parent_name, [])
                
                for child_id in data["children"]:
                    # 해당 자식 카테고리의 이름 찾기
                    cursor.execute(f"SELECT name FROM notification_category WHERE notification_category_id = {child_id}")
                    category_name = cursor.fetchone()[0]
                    
                    # 템플릿이 있는 카테고리만 처리
                    if category_name in notification_templates:
                        all_category_ids.append(child_id)
                        category_map[child_id] = category_name
            
            # 알림 생성
            for i in range(num_notifications):
                member_id = random.choice(member_ids)
                
                # 카테고리 ID와 이름 선택
                notification_category_id = random.choice(all_category_ids)
                category_name = category_map[notification_category_id]
                
                # 해당 카테고리의 템플릿에서 제목과 내용 선택
                templates = notification_templates.get(category_name, notification_templates["공지사항"])
                
                title_template = random.choice(templates["titles"])
                content_template = random.choice(templates["contents"])
                url_template = random.choice(templates["urls"])
                
                # 템플릿 값 설정
                replacements = {
                    "{sender_name}": fake.name(),
                    "{project_title}": fake.catch_phrase(),
                    "{point_amount}": str(random.randint(10, 1000)),
                    "{activity_name}": random.choice(["프로필 완성", "매칭 성공", "리뷰 작성", "커뮤니티 활동"]),
                    "{request_id}": str(random.randint(1000, 9999))
                }
                
                # 템플릿 치환
                title = title_template
                content = content_template
                url = url_template
                
                for placeholder, value in replacements.items():
                    title = title.replace(placeholder, value)
                    content = content.replace(placeholder, value)
                    url = url.replace(placeholder, value)
                
                # 발송 시간과 읽은 시간 설정 (30%는 읽지 않음)
                sent_at = fake.date_time_between(start_date='-6m', end_date='now')
                read_at = fake.date_time_between(start_date=sent_at, end_date='now') if random.random() < 0.7 else None
                
                cursor.execute(sql, (member_id, notification_category_id, title, content, url, sent_at, read_at))
                
                if (i + 1) % 1000 == 0:
                    conn.commit()
                    print(f"{i + 1}개 알림 데이터 삽입됨.")
            
            conn.commit()
            print(f"총 {num_notifications}개의 알림 데이터 삽입 완료!")
            
    finally:
        conn.close()

# 단독 실행 시 사용
if __name__ == "__main__":
    from modules.common import get_connection
    from modules.member import insert_members
    from modules.notification import insert_notification_categories
    
    # 테스트용 멤버 생성
    member_ids = insert_members(100)
    notification_category_ids = insert_notification_categories()
    
    # 수정된 알림 삽입 함수 실행
    fix_notifications(member_ids, notification_category_ids, 500) 