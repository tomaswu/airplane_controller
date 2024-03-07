#! python3
# -*- encoding: utf-8 -*-
"""
@File    :   devsocket.py
@Time    :   24-03-07
@Version :   1.0
@Author  :   Tomas 
@Contact :   tomaswu@qq.com
@Desc    :   
"""

import socket
from multiprocessing.dummy import Pool, Process
import time
from PySide6 import QtCore, QtWidgets, QtGui


class controlFlag():
    def __init__(self):
        self.run_flag = True
        self.is_busy = False
        self.err_already_set = False
        self.recvdata = ''
        self.err = ''
    
    def __str__(self) -> str:
        return f'run flag:{self.run_flag}  busy?:{self.is_busy} err:{self.err}'

def commu(conn: socket.socket, addr, flag: controlFlag):
    print(f'start new thread...{flag}')
    try:
        flag.isBusy = True
        conn.setblocking(0)
        conn.settimeout(0.05)
        while flag.run_flag:
            print('ready send:', f'test {time.time()}')
            conn.send(f'test {time.time()}'.encode())
            try:
                data = conn.recv(1024)
                print('get recv:',data)
            except:
                pass
            
            print('send over!')
            time.sleep(1)
        flag.is_busy = False
    except Exception as e:
        print('error')
        flag.run_flag = False
        flag.err_already_set = True
        flag.err = f'socket 异常退出:{e}'
        print(flag.err)
    finally:
        print('thread stop!')


class form(QtWidgets.QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle('socket 虚拟服务测试')
        self.pool = Pool(processes=5)
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.flag_list = []
        self.HOST = '127.0.0.1'
        self.PORT = 0xf142
        print(self.HOST, self.PORT)
        self.sock.bind((self.HOST, self.PORT))
        self.sock.listen(5)
        self.p = Process(target=self.listen)
        self.p.daemon = True
        self.p.start()
        self.resize(280,60)
        self.label = QtWidgets.QLabel(self,text='测试用虚拟设备,running...')
        self.timer = QtCore.QTimer()
        self.timer.timeout.connect(self.runAnim)
        self.timer.start(800)

    def runAnim(self):
        self.label.setStyleSheet(f"color:{['red','green'][int(time.time()*1000/800)%2]}")

    def listen(self):
        while True:
            conn, addr = self.sock.accept()
            self.flag_list.append(controlFlag())
            self.pool.apply_async(commu, (conn, addr, self.flag_list[-1]))
            print(f'{addr} connected\n')
            time.sleep(0.01)

if __name__ == '__main__':
    app = QtWidgets.QApplication()
    w = form()
    w.show()
    app.exec()
