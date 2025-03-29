USE zto_local_core;
ALTER DATABASE zto_local_core
  DEFAULT CHARACTER SET utf8mb4
  DEFAULT COLLATE utf8mb4_unicode_ci;

SET FOREIGN_KEY_CHECKS = 0;
DROP TABLE IF EXISTS `study_dashboard`;
DROP TABLE IF EXISTS `dashboard_category`;
DROP TABLE IF EXISTS `attendance`;
DROP TABLE IF EXISTS `daily_study_content`;
DROP TABLE IF EXISTS `study_space`;
DROP TABLE IF EXISTS `follow`;
DROP TABLE IF EXISTS `retrospect`;
DROP TABLE IF EXISTS `experience`;
DROP TABLE IF EXISTS `member_point`;
DROP TABLE IF EXISTS `member_rating`;
DROP TABLE IF EXISTS `comment`;
DROP TABLE IF EXISTS `project_func`;
DROP TABLE IF EXISTS `notification_reservation`;
DROP TABLE IF EXISTS `notification`;
DROP TABLE IF EXISTS `notification_setting`;
DROP TABLE IF EXISTS `notification_category`;
DROP TABLE IF EXISTS `matching_request_partner`;
DROP TABLE IF EXISTS `matching_request`;
DROP TABLE IF EXISTS `matching_template`;
DROP TABLE IF EXISTS `matching_template_detail`;
DROP TABLE IF EXISTS `skill_category`;
DROP TABLE IF EXISTS `matching_field`;
DROP TABLE IF EXISTS `blacklist`;
DROP TABLE IF EXISTS `member_detail`;
DROP TABLE IF EXISTS `tech_stack_ref`;
DROP TABLE IF EXISTS `tech_stack`;
DROP TABLE IF EXISTS `social_media`;
DROP TABLE IF EXISTS `social_media_type`;
DROP TABLE IF EXISTS `resized_image`;
DROP TABLE IF EXISTS `member_profile`;
DROP TABLE IF EXISTS `image`;
DROP TABLE IF EXISTS `member`;
SET FOREIGN_KEY_CHECKS = 1;


CREATE TABLE `member` (
  `member_id` bigint PRIMARY KEY AUTO_INCREMENT,
  `login_id` varchar(255) NOT NULL,
  `phone` varchar(255) NOT NULL,
  `name` varchar(255) NOT NULL,
  `created_at` timestamp NOT NULL,
  `updated_at` timestamp NOT NULL,
  -- ENUM('ACTIVE','INACTIVE') -> VARCHAR(8)
  `member_status` varchar(8) NOT NULL DEFAULT 'ACTIVE',
  -- ENUM('F','T') -> CHAR(1)
  `auto_matching` char(1) NOT NULL DEFAULT 'F',
  -- ENUM('ROLE_MEMBER') -> VARCHAR(20)
  `role` varchar(20) NOT NULL DEFAULT 'ROLE_MEMBER'
);

CREATE TABLE `member_profile` (
  `member_id` bigint PRIMARY KEY,
  `nickname` varchar(255),
  `profile_intro` varchar(255),
  `image_id` bigint,
  `created_at` timestamp NOT NULL,
  `updated_at` timestamp NOT NULL
);

CREATE TABLE `image` (
  `image_id` bigint PRIMARY KEY AUTO_INCREMENT,
  `original_image_url` varchar(255) NOT NULL,
  `created_at` timestamp NOT NULL,
  `updated_at` timestamp NOT NULL
);

CREATE TABLE `resized_image` (
  `image_resized_id` bigint PRIMARY KEY AUTO_INCREMENT,
  `image_id` bigint NOT NULL,
  -- ENUM('THUMB','SMALL','LARGE','ETC') -> VARCHAR(10)
  `resized_image_url` varchar(255) NOT NULL,
  `resizing_type` varchar(10) NOT NULL
);

CREATE TABLE `social_media_type` (
  `social_media_type_id` int PRIMARY KEY AUTO_INCREMENT,
  `type_name` varchar(100) NOT NULL,
  `description` varchar(255),
  `image_id` bigint
);

CREATE TABLE `social_media` (
  `social_media_id` int PRIMARY KEY AUTO_INCREMENT,
  `member_id` bigint NOT NULL,
  `social_media_type_id` int NOT NULL,
  `url` varchar(255) NOT NULL,
  `created_at` timestamp NOT NULL,
  `updated_at` timestamp NOT NULL
);

CREATE TABLE `tech_stack` (
  `tech_stack_id` int PRIMARY KEY AUTO_INCREMENT,
  `tech_stack_name` varchar(100) NOT NULL,
  `parent_id` int,
  `level` int,
  `image_id` bigint,
  `created_at` timestamp NOT NULL,
  `updated_at` timestamp NOT NULL
);

CREATE TABLE `tech_stack_ref` (
  `tech_stack_ref_id` bigint PRIMARY KEY AUTO_INCREMENT,
  `tech_stack_id` int NOT NULL,
  `member_id` bigint NOT NULL
);

CREATE TABLE `member_detail` (
  `member_id` bigint PRIMARY KEY,
  `nickname` varchar(255),
  `profile_image` varchar(255),
  `bio` varchar(255),
  `created_at` timestamp NOT NULL,
  `updated_at` timestamp NOT NULL
);

CREATE TABLE `blacklist` (
  `blacklist_id` bigint PRIMARY KEY AUTO_INCREMENT,
  `member_id` bigint NOT NULL,
  `reason` varchar(255),
  `created_at` timestamp NOT NULL
);

CREATE TABLE `matching_field` (
  `matching_field_id` int PRIMARY KEY AUTO_INCREMENT,
  `field_name` varchar(50) NOT NULL,
  `weight` int NOT NULL,
  `created_at` timestamp,
  `updated_at` timestamp
);

CREATE TABLE `skill_category` (
  `skill_type_id` int PRIMARY KEY AUTO_INCREMENT,
  `skill_type_name` varchar(100) UNIQUE,
  `code` char(3),
  `depth` int NOT NULL DEFAULT 0,
  `parent_id` int
);

CREATE TABLE `matching_template_detail` (
  `detail_id` bigint PRIMARY KEY AUTO_INCREMENT,
  `template_id` bigint NOT NULL,
  `matching_field_id` int NOT NULL,
  `skill_type_id` int,
  `weight` DECIMAL(5,2) NOT NULL,
  -- ENUM('=','>=','<=','!=','>') -> VARCHAR(2)
  `operator` varchar(2),
  `value` varchar(255),
  `order_seq` int NOT NULL,
  `created_at` timestamp NOT NULL,
  `updated_at` timestamp NOT NULL
);

CREATE TABLE `matching_template` (
  `template_id` bigint PRIMARY KEY AUTO_INCREMENT,
  `name` varchar(50) NOT NULL COMMENT '학습분야우선매칭, 평점우선매칭',
  `description` varchar(255),
  `created_at` timestamp NOT NULL,
  `updated_at` timestamp
);

CREATE TABLE `matching_request` (
  `matching_id` bigint PRIMARY KEY AUTO_INCREMENT,
  `member_id` bigint NOT NULL,
  `partner_id` bigint,
  `template_id` bigint,
  -- ENUM('PENDING','ACCEPTED','CANCELED','REJECTED','AUTO','DONE') -> VARCHAR(8)
  `status` varchar(8) NOT NULL COMMENT '1. 확인중 2. 수락됨(진행중) 3. 취소 4. 거절 5. 자동 매칭중 6. 매칭 완료',
  -- ENUM('AUTO','MANUAL') -> VARCHAR(6)
  `type` varchar(6) NOT NULL COMMENT '자동매칭, 수동매칭',
  `content` varchar(55),
  -- ENUM('TRUE','FALSE') -> CHAR(5)
  `deleted` char(5) NOT NULL DEFAULT 'FALSE',
  `created_at` timestamp NOT NULL,
  `updated_at` timestamp NOT NULL
);

CREATE TABLE `matching_request_partner` (
  `result_id` bigint PRIMARY KEY AUTO_INCREMENT,
  `matching_id` bigint NOT NULL,
  `partner_id` bigint NOT NULL,
  -- ENUM('DONE','CANCEL') -> VARCHAR(6)
  `status` varchar(6) NOT NULL,
  `cancel_reason` varchar(255),
  `matched_at` timestamp NOT NULL,
  `updated_at` timestamp
);

CREATE TABLE `notification_setting` (
  `notification_id` bigint PRIMARY KEY AUTO_INCREMENT,
  `member_id` bigint UNIQUE NOT NULL,
  `notification_category_id` bigint UNIQUE NOT NULL,
  -- ENUM('ON','OFF') -> CHAR(3)
  `status` char(3) NOT NULL
);

CREATE TABLE `notification_category` (
  `notification_category_id` bigint PRIMARY KEY AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  `parent_id` bigint,
  `child_id` bigint,
  `rank` bigint
);

CREATE TABLE `notification` (
  `notification_id` bigint PRIMARY KEY AUTO_INCREMENT,
  `receiver_id` bigint NOT NULL,
  `sender_id` bigint NOT NULL,
  `notification_category_id` bigint NOT NULL,
  `title` varchar(255),
  `content` varchar(255),
  `type` varchar(255) NOT NULL,
  `url` varchar(255),
  `status` varchar(255),
  `created_at` timestamp NOT NULL,
  `updated_at` timestamp
);

CREATE TABLE `notification_reservation` (
  `notification_reservation_id` bigint PRIMARY KEY AUTO_INCREMENT,
  `receiver_id` bigint NOT NULL,
  `content` varchar(255),
  `created_at` timestamp NOT NULL,
  `deleted_at` timestamp
);

CREATE TABLE `project_func` (
  `project_func_id` int PRIMARY KEY NOT NULL,
  `name` varchar(50) NOT NULL,
  `code` char(3) NOT NULL,
  `level` int NOT NULL,
  `parent_id` int NOT NULL
);

CREATE TABLE `comment` (
  `comment_id` bigint PRIMARY KEY AUTO_INCREMENT,
  `member_id` bigint NOT NULL,
  `project_func_id` int NOT NULL,
  `created_at` timestamp NOT NULL,
  `updated_at` timestamp NOT NULL,
  -- ENUM('TRUE','FALSE') -> CHAR(5)
  `deleted` char(5) NOT NULL DEFAULT 'FALSE',
  `description` varchar(255) NOT NULL,
  `level` int NOT NULL DEFAULT 1,
  `parent_comment_id` bigint
);

CREATE TABLE `member_rating` (
  `rate_id` int PRIMARY KEY AUTO_INCREMENT,
  `member_id` bigint NOT NULL,
  `project_func_id` int NOT NULL,
  `rate` double NOT NULL
);

CREATE TABLE `member_point` (
  `member_point_id` bigint PRIMARY KEY AUTO_INCREMENT,
  `member_id` bigint NOT NULL,
  `project_func_id` int NOT NULL,
  `current_point` bigint NOT NULL DEFAULT 0,
  `updated_at` timestamp NOT NULL DEFAULT (CURRENT_TIMESTAMP)
);

CREATE TABLE `experience` (
  `experience_id` bigint PRIMARY KEY AUTO_INCREMENT,
  `member_id` bigint NOT NULL,
  `project_func_id` int,
  `amount` int NOT NULL DEFAULT 0,
  `created_at` timestamp NOT NULL
);

CREATE TABLE `retrospect` (
  `retrospect_id` bigint PRIMARY KEY AUTO_INCREMENT,
  `project_func_id` int NOT NULL,
  -- ENUM('TRUE','FALSE') -> CHAR(5)
  `deleted` char(5) NOT NULL DEFAULT 'FALSE',
  `created_at` timestamp NOT NULL,
  `updated_at` timestamp NOT NULL,
  `description` varchar(255) NOT NULL,
  `parent_id` bigint NOT NULL
);

CREATE TABLE `follow` (
  `follower_id` bigint NOT NULL,
  `followed_id` bigint NOT NULL,
  `created_at` timestamp NOT NULL,
  PRIMARY KEY (`follower_id`, `followed_id`)
);

CREATE TABLE `study_space` (
  `study_space_id` bigint PRIMARY KEY AUTO_INCREMENT,
  `scheduled_interview_time` timestamp NOT NULL,
  `subject` varchar(30) NOT NULL,
  -- ENUM('TRUE','FALSE') -> CHAR(5)
  `deleted` char(5) NOT NULL DEFAULT 'FALSE',
  `created_at` timestamp NOT NULL,
  `updated_at` timestamp NOT NULL,
  `personnel_count` int NOT NULL DEFAULT 0
);

CREATE TABLE `daily_study_content` (
  `daily_study_id` bigint PRIMARY KEY AUTO_INCREMENT,
  `member_id` bigint NOT NULL,
  `study_space_id` bigint NOT NULL,
  `description` varchar(255) NOT NULL,
  `created_at` timestamp NOT NULL,
  `updated_at` timestamp NOT NULL,
  `deleted` boolean NOT NULL DEFAULT false,
  `progress_start_time` timestamp NOT NULL,
  -- ENUM('PENDING','IN_PROGRESS','COMPLETE','ABSENT') -> VARCHAR(11)
  `progress_status` varchar(11) NOT NULL DEFAULT 'PENDING',
  `plan_time` timestamp NOT NULL,
  `subject` varchar(50) NOT NULL,
  `link` varchar(50),
  `is_private` boolean NOT NULL DEFAULT false
);

CREATE TABLE `attendance` (
  `attendance_id` bigint PRIMARY KEY AUTO_INCREMENT,
  `daily_study_id` bigint NOT NULL,
  -- ENUM('ATTENDANCE','LATE','ABSENCE') -> VARCHAR(10)
  `status` varchar(10) NOT NULL DEFAULT 'ATTENDANCE',
  `created_at` timestamp NOT NULL,
  `updated_at` timestamp NOT NULL
);

CREATE TABLE `dashboard_category` (
  `dashboard_id` int PRIMARY KEY,
  `name` varchar(50) NOT NULL,
  `code` char(3) NOT NULL,
  `level` int NOT NULL DEFAULT 1,
  `parent_id` int
);

CREATE TABLE `study_dashboard` (
  `study_dashboard_id` bigint PRIMARY KEY AUTO_INCREMENT,
  `dashboard_id` int NOT NULL,
  `member_id` bigint NOT NULL,
  `argument` double NOT NULL DEFAULT 0,
  `created_at` timestamp NOT NULL,
  `updated_at` timestamp NOT NULL
);

-- ALTER TABLE `member_profile` ADD FOREIGN KEY (`image_id`) REFERENCES `image` (`image_id`);
-- ALTER TABLE `resized_image` ADD FOREIGN KEY (`image_id`) REFERENCES `image` (`image_id`);
-- ALTER TABLE `social_media_type` ADD FOREIGN KEY (`image_id`) REFERENCES `image` (`image_id`);
-- ALTER TABLE `social_media` ADD FOREIGN KEY (`social_media_type_id`) REFERENCES `social_media_type` (`social_media_type_id`);
-- ALTER TABLE `social_media` ADD FOREIGN KEY (`member_id`) REFERENCES `member_profile` (`member_id`);
-- ALTER TABLE `tech_stack` ADD FOREIGN KEY (`parent_id`) REFERENCES `tech_stack` (`tech_stack_id`);
-- ALTER TABLE `tech_stack` ADD FOREIGN KEY (`image_id`) REFERENCES `image` (`image_id`);
-- ALTER TABLE `tech_stack_ref` ADD FOREIGN KEY (`tech_stack_id`) REFERENCES `tech_stack` (`tech_stack_id`);
-- ALTER TABLE `tech_stack_ref` ADD FOREIGN KEY (`member_id`) REFERENCES `member_profile` (`member_id`);
-- ALTER TABLE `member_detail` ADD FOREIGN KEY (`member_id`) REFERENCES `member` (`member_id`);
-- ALTER TABLE `blacklist` ADD FOREIGN KEY (`member_id`) REFERENCES `member` (`member_id`);
-- ALTER TABLE `skill_category` ADD FOREIGN KEY (`parent_id`) REFERENCES `skill_category` (`skill_type_id`);
-- ALTER TABLE `matching_template_detail` ADD FOREIGN KEY (`matching_field_id`) REFERENCES `matching_field` (`matching_field_id`);
-- ALTER TABLE `matching_template_detail` ADD FOREIGN KEY (`skill_type_id`) REFERENCES `skill_category` (`skill_type_id`);
-- ALTER TABLE `matching_template_detail` ADD FOREIGN KEY (`template_id`) REFERENCES `matching_template` (`template_id`);
-- ALTER TABLE `matching_request` ADD FOREIGN KEY (`template_id`) REFERENCES `matching_template` (`template_id`);
-- ALTER TABLE `matching_request` ADD FOREIGN KEY (`member_id`) REFERENCES `member` (`member_id`);
-- ALTER TABLE `matching_request` ADD FOREIGN KEY (`partner_id`) REFERENCES `member` (`member_id`);
-- ALTER TABLE `matching_request_partner` ADD FOREIGN KEY (`matching_id`) REFERENCES `matching_request` (`matching_id`);
-- ALTER TABLE `matching_request_partner` ADD FOREIGN KEY (`partner_id`) REFERENCES `member` (`member_id`);
-- ALTER TABLE `notification_setting` ADD FOREIGN KEY (`member_id`) REFERENCES `member` (`member_id`);
-- ALTER TABLE `notification_setting` ADD FOREIGN KEY (`notification_category_id`) REFERENCES `notification_category` (`notification_category_id`);
-- ALTER TABLE `notification` ADD FOREIGN KEY (`notification_category_id`) REFERENCES `notification_category` (`notification_category_id`);
-- ALTER TABLE `notification` ADD FOREIGN KEY (`receiver_id`) REFERENCES `member` (`member_id`);
-- ALTER TABLE `notification` ADD FOREIGN KEY (`sender_id`) REFERENCES `member` (`member_id`);
-- ALTER TABLE `notification_reservation` ADD FOREIGN KEY (`receiver_id`) REFERENCES `member` (`member_id`);
-- ALTER TABLE `retrospect` ADD FOREIGN KEY (`project_func_id`) REFERENCES `project_func` (`project_func_id`);
-- ALTER TABLE `comment` ADD FOREIGN KEY (`member_id`) REFERENCES `member` (`member_id`);
-- ALTER TABLE `comment` ADD FOREIGN KEY (`project_func_id`) REFERENCES `project_func` (`project_func_id`);
-- ALTER TABLE `member_profile` ADD FOREIGN KEY (`member_id`) REFERENCES `member` (`member_id`);
-- ALTER TABLE `member_rating` ADD FOREIGN KEY (`member_id`) REFERENCES `member_profile` (`member_id`);
-- ALTER TABLE `member_rating` ADD FOREIGN KEY (`project_func_id`) REFERENCES `project_func` (`project_func_id`);
-- ALTER TABLE `member_point` ADD FOREIGN KEY (`project_func_id`) REFERENCES `project_func` (`project_func_id`);
-- ALTER TABLE `member_point` ADD FOREIGN KEY (`member_id`) REFERENCES `member_profile` (`member_id`);
-- ALTER TABLE `experience` ADD FOREIGN KEY (`member_id`) REFERENCES `member_profile` (`member_id`);
-- ALTER TABLE `experience` ADD FOREIGN KEY (`project_func_id`) REFERENCES `project_func` (`project_func_id`);
-- ALTER TABLE `follow` ADD FOREIGN KEY (`follower_id`) REFERENCES `member` (`member_id`);
-- ALTER TABLE `follow` ADD FOREIGN KEY (`followed_id`) REFERENCES `member` (`member_id`);
-- ALTER TABLE `daily_study_content` ADD FOREIGN KEY (`member_id`) REFERENCES `member` (`member_id`);
-- ALTER TABLE `daily_study_content` ADD FOREIGN KEY (`study_space_id`) REFERENCES `study_space` (`study_space_id`);
-- ALTER TABLE `attendance` ADD FOREIGN KEY (`daily_study_id`) REFERENCES `daily_study_content` (`daily_study_id`);
-- ALTER TABLE `study_dashboard` ADD FOREIGN KEY (`dashboard_id`) REFERENCES `dashboard_category` (`dashboard_id`);
