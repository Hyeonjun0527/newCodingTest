import sys
import os

from modules.common import get_connection, truncate_tables, print_table_counts
from modules.member import insert_members, insert_member_profiles, insert_member_details, insert_blacklist, insert_follows
from modules.image import insert_images, insert_resized_images
from modules.matching import insert_matching_fields, insert_skill_categories, insert_matching_templates, insert_matching_template_details, insert_matching_requests, insert_matching_request_partners
from modules.notification import insert_notification_categories, insert_notification_settings, insert_notifications, insert_notification_reservations
from modules.social import insert_social_media_types, insert_social_media, insert_tech_stacks, insert_tech_stack_refs
from modules.project import insert_project_funcs, insert_comments, insert_member_ratings, insert_member_points, insert_experiences, insert_retrospects
from modules.study import insert_study_spaces, insert_daily_study_contents, insert_attendances, insert_dashboard_categories, insert_study_dashboards

def main():
    try:
        # MySQL 연결 확인
        conn = get_connection()
        conn.close()
        print("MySQL 연결 성공!")
        
        # 기존 데이터 삭제
        truncate_tables()
        
        # 이미지 데이터 삽입
        image_ids = insert_images(num_images=5000)
        insert_resized_images(image_ids)
        
        # 멤버 데이터 삽입
        member_ids = insert_members(num_records=1000)
        
        # 멤버 프로필 데이터 삽입
        member_profile_ids = insert_member_profiles(member_ids, image_ids)
        
        # 회원 상세정보 및 블랙리스트 데이터 삽입
        insert_member_details(member_ids)
        insert_blacklist(member_ids, num_blacklist=100)
        
        # 팔로우 데이터 삽입
        insert_follows(member_ids, num_follows=2000)
        
        # 매칭 필드 및 스킬 카테고리 데이터 삽입
        matching_field_ids = insert_matching_fields()
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
        notification_categories = insert_notification_categories()
        notification_category_ids = [cat_id for cat_id, _, _ in notification_categories]
        insert_notification_settings(member_ids)
        insert_notifications(
            member_ids, 
            notification_categories, 
            project_ids=None,
            project_func_ids=None,
            study_ids=None,
            num_notifications=2000
        )
        insert_notification_reservations(member_ids, notification_category_ids, num_reservations=100)
        
        # 프로젝트 기능 및 관련 데이터 삽입
        project_func_ids = insert_project_funcs()
        insert_comments(member_ids, project_func_ids)
        insert_member_ratings(member_ids, project_func_ids)
        insert_member_points(member_ids)
        insert_experiences(member_ids, project_func_ids)
        insert_retrospects(member_ids, project_func_ids)
        
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
        
    except Exception as e:
        print(f"에러 발생: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()