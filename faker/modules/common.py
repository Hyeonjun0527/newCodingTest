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

def print_table_counts():
    conn = get_connection()
    
    try:
        with conn.cursor() as cursor:
            for table, description in TABLES.items():
                try:
                    cursor.execute(f"SELECT COUNT(*) FROM {table}")
                    count = cursor.fetchone()[0]
                    print(f"{description} ({table}): {count}개")
                except Exception as e:
                    print(f"{table} 테이블 조회 중 오류 발생: {e}")
            
    finally:
        conn.close() 