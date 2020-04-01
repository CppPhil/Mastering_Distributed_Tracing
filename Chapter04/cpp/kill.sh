#!/bin/bash

pkill -f ./bigbrother_service/bigbrother_app
pkill -f ./formatter_service/formatter_app 
pkill -f ./main_app/main_app

exit 0

