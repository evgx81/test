from faker import Faker
import cjson
import ujson
import json

def test_json(json_str: str):
    _ = json.loads(json_str) 

def test_ujson(json_str: str):
    _ = ujson.loads(json_str) 

def test_cjson(json_str: str):
    _ = cjson.loads(json_str) 

if __name__ == '__main__':
    Faker.seed(0)
    faker = Faker()
    json_str = "{"
    for _ in range(1000):
        json_str += f'"{faker.numerify(text="keyword%")}": "{faker.name()}",'
    json_str += f'"{faker.numerify(text="keyword%")}": "{faker.name()}"'
    json_str += "}"
    
    test_json(json_str)
    test_ujson(json_str)
    test_cjson(json_str)