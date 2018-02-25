FROM alpine:3.7

# Include following if proxies are needed:
#ENV http_proxy 'http://url'
#ENV https_proxy 'https://url'
#ENV HTTP_PROXY 'http://url'
#ENV HTTPS_PROXY 'https://url'


RUN apk update && apk add mongodb python python-dev python3 python3-dev py-pip acf-openssl openssl-dev openssl libffi libffi-dev ca-certificates gcc build-base
    
EXPOSE 1337
EXPOSE 1338

WORKDIR /bank
ADD bank_server ./bank_server
RUN mkdir /bank/bank_server/logs
RUN python -m pip install pymongo pyyaml nose flask flask-sslify pyopenssl
RUN mkdir -p /data/certs
RUN openssl req -new -newkey rsa:4096 -days 365 -nodes -x509 -subj "/C=US/ST=NE/L=Omaha/O=Nullify/CN=localhost" -keyout /data/certs/key.pem -out /data/certs/cert.pem
ADD setup.py ./setup.py
ADD setup.sh ./setup.sh
ADD README.md ./README.md
RUN python setup.py install
CMD /bin/sh /bank/setup.sh && /bin/sh
