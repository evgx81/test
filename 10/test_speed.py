from faker import Faker
import cjson
import ujson
import json

def test_json_01(json_str: str):
    _ = json.loads(json_str) 

def test_ujson_02(json_str: str):
    _ = ujson.loads(json_str) 

def test_cjson_03(json_str: str):
    _ = cjson.loads(json_str)

def test_json_04(d):
    _ = json.dumps(d) 

def test_ujson_05(d):
    _ = ujson.dumps(d) 

def test_cjson_06(d):
    _ = cjson.dumps(d) 

if __name__ == '__main__':
    Faker.seed(0)
    faker = Faker()
    json_str = "{"
    for _ in range(1000):
        json_str += f'"{faker.numerify(text="keyword%")}": "{faker.name()}",'
    json_str += f'"{faker.numerify(text="keyword%")}": "{faker.name()}"'
    json_str += "}"

    d = {"Key1":"Val1", "Key2":"Val2"}
    
    test_json_01(json_str)
    test_ujson_02(json_str)
    test_cjson_03(json_str)

    test_json_04(json_str)
    test_ujson_05(json_str)
    test_cjson_06(json_str)