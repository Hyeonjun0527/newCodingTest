from .common import get_connection, fake
import random
import uuid

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