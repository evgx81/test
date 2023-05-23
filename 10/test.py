import cjson

json = '({"Key_1": "Value_1", "Key_2": "Value_2"})'
d = cjson.loads(json)
print(d)

s = cjson.dumps(d)
print(s)