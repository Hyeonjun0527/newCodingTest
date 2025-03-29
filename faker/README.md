# ZTO_LOCAL 테스트 데이터 생성기

이 프로젝트는 ZTO_LOCAL 데이터베이스를 위한 테스트 데이터 생성기입니다. 다양한 테이블에 대해 가상의 데이터를 생성하여 테스트 환경을 구성할 수 있습니다.

## 모듈 구조

프로젝트는 아래와 같은 모듈 구조로 될 예정입니다.

```
faker/
├── modules/                     # 각 도메인별 모듈 디렉토리
│   ├── __init__.py             # 모듈 패키지 초기화
│   ├── common.py               # 공통 함수와 상수 정의
│   ├── member.py               # 회원 관련 함수
│   ├── image.py                # 이미지 관련 함수
│   ├── matching.py             # 매칭 관련 함수
│   ├── notification.py         # 알림 관련 함수
│   ├── project.py              # 프로젝트 기능, 회고, 댓글 등 관련 함수
│   ├── social.py               # 소셜 미디어, 기술 스택 관련 함수
│   └── study.py                # 스터디, 대시보드 관련 함수
├── main.py                      # 메인 실행 파일
├── notification_fix.py          # notification.py 수정본
├── README.md                    # 프로젝트 설명
├── ZTO_LOCAL_DDL.sql            # 데이터베이스 테이블 정의
```

현재 상태론 ZTO_LOCAL_INIT.py 이곳에 전부 때려박았습니다. 수정할 예정입니다.

## 기능

이 데이터 생성기는 다음 테이블들에 대한 테스트 데이터를 생성합니다:

1. 회원 관련: member, member_profile, member_detail, blacklist, follow
2. 이미지 관련: image, resized_image
3. 매칭 관련: matching_field, skill_category, matching_template, matching_template_detail, matching_request, matching_request_partner
4. 알림 관련: notification_category, notification_setting, notification, notification_reservation
5. 소셜 및 기술 스택: social_media_type, social_media, tech_stack, tech_stack_ref
6. 프로젝트 관련: project_func, comment, member_rating, member_point, experience, retrospect
7. 스터디 관련: study_space, daily_study_content, attendance, dashboard_category, study_dashboard

## 사용 방법

### 설치

1. 필요한 패키지 설치:
```bash
pip install faker pymysql
```

2. 데이터베이스 설정:
- MySQL에 'zto_local_core' 데이터베이스를 생성합니다.
- ZTO_LOCAL_DDL.sql을 실행하여 필요한 테이블들을 생성합니다.

### 실행

전체 데이터 생성:
```bash
python ZTO_LOCAL_INIT.py
```

## 커스터마이징

각 테이블의 데이터 생성 수를 조정하려면 `main.py` 파일의 각 함수 호출 부분에서 파라미터를 수정하면 됩니다.
그리고 현재 예제 데이터가 테이블간의 관계를 고려하여 생성된 데이터임은 맞지만,
GPT가 만들어준 것이라 저희 도메인과 온전히 일치하는 예제 데이터는 아닌 상황입니다.
이걸 각 도메인 담당하시는 분께서 코드를 수정해주시면 감사하겠습니다.

예시:
```python
# 회원 수를 5000명으로 조정
member_ids = insert_members(5000)

# 이미지 수를 2000개로 조정
image_ids = insert_images(2000)
```

## 주의사항

1. 데이터베이스 연결 정보 (common.py의 get_connection 함수):
   - 기본값은 localhost의 root 사용자, 비밀번호 'root'로 설정되어 있습니다.
   - 필요에 따라 이 정보를 수정하여 사용하세요.

2. 대량의 데이터 생성 시 시간이 오래 걸릴 수 있습니다.

3. 실행 전 기존 데이터를 모두 삭제합니다 (truncate_tables 함수 호출). 