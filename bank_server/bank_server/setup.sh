#!/bin/sh
mkdir -p /data/db
mongod &
python -m bank_server.__main__