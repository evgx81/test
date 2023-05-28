#! /usr/bin/env python3

from unittest import TestCase, main
from faker import Faker

import cjson

class TestParseJson(TestCase):
    """
    Тесты для функции parse_json
    В данном случае у нас сгенерируется следующий json:
    {
        "keyword7": "Jennifer Green",
        "keyword9": "Dr. Ronald Faulkner",
        "keyword6": "Susan Wagner",
        "keyword5": "Brandon Lloyd"
    }
    """

    def setUp(self):
        # Фиксируем сгенерированные данные
        Faker.seed(0)

        faker = Faker()

        self.json_str = "{"
        for _ in range(3):
            self.json_str += \
                f'"{faker.numerify(text="keyword%")}": "{faker.name()}",'
        self.json_str += \
            f'"{faker.numerify(text="keyword%")}": "{faker.name()}"'
        self.json_str += "}"

    def test_loads_01(self):
        cjson_dict = cjson.loads(self.json_str)
        self.assertEqual(cjson_dict["keyword7"], "Jennifer Green")
        self.assertEqual(cjson_dict["keyword9"], "Dr. Ronald Faulkner")
        self.assertEqual(cjson_dict["keyword6"], "Susan Wagner")
        self.assertEqual(cjson_dict["keyword5"], "Brandon Lloyd")

    def test_loads_02(self):
        d = {"Key1":"Val1", "Key2":"Val2"}
        cjson_str = cjson.dumps(d)
        self.assertEqual(cjson_str, "{\"Key_1\":\"Value_1\",\"Key_2\":\"Value_2\"}")


if __name__ == "__main__":
    main()