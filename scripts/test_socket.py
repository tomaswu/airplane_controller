#! python3
# -*- encoding: utf-8 -*-
"""
@File    :   test_socket.py
@Time    :   24-03-07
@Version :   1.0
@Author  :   Tomas 
@Contact :   tomaswu@qq.com
@Desc    :   
"""
import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
flag_list = []
HOST='127.0.0.1'
PORT=0xf142
print(HOST,PORT)
sock.connect((HOST, PORT))

while True:
    data = sock.recv(1024)
    # sock.sendall('test')
    print(data)