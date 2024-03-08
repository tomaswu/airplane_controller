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
import queue
import json
import logging


class LOG():
    def __init__(self, file='uavbrain.log'):
        self._log_file = file
        self._Fhandler = logging.FileHandler(
            self._log_file, mode='w', encoding='utf-8')
        self._Chandler = logging.StreamHandler()
        self._fmt = '%(asctime)s - %(filename)s - %(funcName)s - %(lineno)s - %(levelname)s : %(message)s'
        self._formatter = logging.Formatter(self._fmt)
        self._Chandler.setFormatter(self._formatter)
        self._Fhandler.setFormatter(self._formatter)
        self.log = logging.getLogger('logger')
        self.log.setLevel(logging.DEBUG)
        self.log.addHandler(self._Fhandler)
        self.log.addHandler(self._Chandler)
        self.level = logging.DEBUG

    def debug(self, *argv):
        self.log.debug(*argv)

    def info(self, *argv):
        self.log.info(*argv)

    def warning(self, *argv):
        self.log.warning(*argv)

    def error(self, *argv):
        self.log.error(*argv)

    def __call__(self, *argv):
        s = ' '.join([i.__str__() for i in argv])
        match self.level:
            case logging.DEBUG:
                self.debug(s)
            case logging.INFO:
                self.info(s)
            case logging.WARNING:
                self.warning(s)
            case logging.ERROR:
                self.error(s)

class controlFlag():
    def __init__(self):
        self.run_flag = True
        self.is_busy = False
        self.err_already_set = False
        self.recvdata = ''
        self.err = ''
        self.que = queue.Queue()
        self.colsed = False

    def __str__(self) -> str:
        return f'run flag:{self.run_flag}  busy?:{self.is_busy} err:{self.err}'

class MainForm(QtWidgets.QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle('socket 虚拟服务测试')
        self.pool = Pool(processes=5)
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.flag_dict = {}
        self.HOST = '127.0.0.1'
        self.PORT = 0xf142
        self.log = LOG()
        self.sock.bind((self.HOST, self.PORT))
        self.sock.listen(5)
        self.p = Process(target=self.listen)
        self.p.daemon = True
        self.p.start()
        self.resize(280, 60)
        self.label = QtWidgets.QLabel(self, text='测试用虚拟设备,running...')
        self.timer = QtCore.QTimer()
        self.timer.timeout.connect(self.runAnim)
        self.timer.start(800)
        self.setTray()

    def setTray(self):
        self.sysTray = QtWidgets.QSystemTrayIcon(self)
        self.sysTray.setIcon(QtGui.QIcon('controller/icos/connect.svg'))
        self.systrayMenu = QtWidgets.QMenu()
        self.sys_ac_quit = QtGui.QAction('quit')
        self.sys_ac_quit.triggered.connect(QtWidgets.QApplication.quit)
        self.systrayMenu.addAction(self.sys_ac_quit)
        self.sysTray.setContextMenu(self.systrayMenu)
        self.sysTray.show()

    def runAnim(self):
        self.label.setStyleSheet(
            f"color:{['red','green'][int(time.time()*1000/800)%2]}")

    def listen(self):
        self.log('start listening...')
        while True:
            conn, addr = self.sock.accept()
            print(addr, type(addr))
            self.flag_dict[addr] = controlFlag()
            self.pool.apply_async(self.commu, (conn, addr, self.flag_dict[addr]))
            print(f'{addr} connected\n')
            time.sleep(0.01)
            for i in self.flag_dict:
                if self.flag_dict[i].closed:
                    del self.flag_dict[i]

    def closeEvent(self, event):
        self.hide()
        event.ignore()

    def commu(self, conn: socket.socket, addr, flag: controlFlag):
        self.log(f'start new thread...{flag}')
        try:
            flag.isBusy = True
            conn.setblocking(0)
            conn.settimeout(3)
            while flag.run_flag:
                if flag.que.qsize() > 0:
                    data = flag.que.get()
                    b_data = data.encode()
                    try:
                        conn.send(b_data)
                        rdata = conn.recv(1024)
                    except:
                        self.log(f'cmd failed:{data.decode()}')
                self.log('ready send:', f'test {time.time()}')
                conn.send(f'test {time.time()}'.encode())
                try:
                    data = conn.recv(1024)
                    print('get recv:', data)
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


if __name__ == '__main__':
    app = QtWidgets.QApplication()
    w = MainForm()
    w.show()
    app.exec()
