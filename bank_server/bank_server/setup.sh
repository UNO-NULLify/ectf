#!/bin/sh
mkdir -p /data/db
mongod &
python /bank/bank_server/setup_db.py