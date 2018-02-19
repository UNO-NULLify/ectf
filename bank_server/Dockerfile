FROM alpine:3.7

# Include following if proxies are needed:
#ENV http_proxy 'http://url'
#ENV https_proxy 'https://url'
#ENV HTTP_PROXY 'http://url'
#ENV HTTPS_PROXY 'https://url'


RUN apk update \
    && apk add mongodb && apk add python && apk add py-pip
    
EXPOSE 1337
EXPOSE 1338

WORKDIR /bank
ADD bank_server ./bank_server
RUN mkdir /bank/bank_server/logs
RUN python -m pip install pymongo
ADD setup.py ./setup.py
ADD setup.sh ./setup.sh
ADD README.md ./README.md
RUN python -m pip install pyyaml nose flask
RUN python setup.py install
CMD /bin/sh /bank/setup.sh && /bin/sh
