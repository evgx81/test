all:
	python3 -m venv venv
	. venv/bin/activate
	./venv/bin/python -m pip install -U pip
	./venv/bin/pip install -r requirements.txt 
	./venv/bin/python setup.py install

test: all
	./venv/bin/python test_lib.py

clean:
	rm -rf venv dist build cjson.egg-info
	rm -rf *.o