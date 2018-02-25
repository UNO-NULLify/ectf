build: Dockerfile bank_server/*
	docker build -t new_bank.img .

start: build
	-docker run -p 1337:1337 -p 1338:1338 -t --name new_bank.cont new_bank.img

stop:
	-docker container stop new_bank.cont

clean:
	-docker container stop new_bank.cont
	-docker container rm new_bank.cont

logs:
	docker exec new_bank.cont cat /bank/bank_server/logs/bank_server.log | cat > bank_server.log

# command run unittests in bank_server/tests
test: clean build
	docker run -p 1337:1337 -p 1338:1338 --name new_bank.cont new_bank.img python -m unittest discover
