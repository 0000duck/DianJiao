# -*- coding: utf-8 -*-



import socket
import struct
import time

class Client:
   
    RECV_SIZE = 1024       

   
    def __init__(self, host, port, wait=10, test=False):
        self._host = host  
        self._port = port  
        self._wait = wait  
        self._test = test   
        self._sock = None   

    def check_connec(self):
        return self._sock

   
    def __del__(self):
        if not (self._sock is None):
            self._sock.close()

    
    def call(self, service, method, *args):
        try:
            if self._sock is None:
                self._sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
                self._sock.settimeout(self._wait)
                self._sock.setsockopt(socket.SOL_SOCKET, socket.SO_KEEPALIVE, True)  
                self._sock.connect((self._host, self._port))
            elif self._test:       
                if not self._check():
                    return self.call(service, method, args)    
          
            data = self._encode(service)
            data += self._encode(method)
            data += self._encode(list(args))
            self._sock.sendall(data)
           
            self._buf = ''  
            self._ptr = 0   
            data = self._recv()
            self._buf = None
            return data
        except:
            self._sock.close()     
            self._sock = None
            self._buf = None
            raise

  
    def _check(self):
        try:
            data = self._encode(None)
            data += self._encode('echo')
            data += self._encode(None)
            self._sock.sendall(data)

            self._buf = '' 
            self._ptr = 0  
            data = self._recv()
            self._buf = None
            if data is None:
                return True        
        except:
            pass
        self._sock.close()     
        self._sock = None
        self._buf = None
        return False

  
    def _encode(self, val):
        if val is None:
            return chr(0x00)   # null
        if isinstance(val, bool):
            return chr(0x01) if val else chr(0x02)   
        if isinstance(val, int):
            return self._encodeType(0x03, val)
        if isinstance(val, float):
            val = str(val)
            return self._encodeType(0x05, len(val)) + val  
        if isinstance(val, time.struct_time):
            val = int(time.mktime(val))
            return self._encodeType(0x06, val)
        if isinstance(val, long):
            val = str(val)
            return self._encodeType(0x07, len(val)) + val
        if isinstance(val, (str, unicode)):
            val = val.encode('utf-8')           
            return self._encodeType(0x10, len(val)) + val
        if isinstance(val, tuple):
            val = ''.join(chr(x) for x in val)
            return self._encodeType(0x20, len(val)) + val
        if isinstance(val, list):
            ss = self._encodeType(0x30, len(val))
            for x in val:
                ss += self._encode(x)
            return ss
        if isinstance(val, dict):
            ss = self._encodeType(0x31, len(val))
            for x in val:
                ss += self._encode(x)
                ss += self._encode(val[x])
            return ss
        raise Exception('data type invalid')  

   
    def _encodeType(self, dtype, size):
        return struct.pack('<BI', 0xc0 + dtype, size)

    
    def _recv(self):
        if self._ptr >= len(self._buf):
            self._recvMore()
        dtype = ord(self._buf[self._ptr])
        self._ptr += 1
        if dtype == 0x00:       # null
            return None
        if dtype == 0x01:       # true
            return True
        if dtype == 0x02:       # false
            return False
        lsize = (dtype >> 6) + 1
        dtype &= 0x3f
        while self._ptr + lsize > len(self._buf):
            self._recvMore()
        size = ord(self._buf[self._ptr])
        for x in xrange(1, lsize):
            size |= ord(self._buf[self._ptr+x]) << (8 * x)
        self._ptr += lsize
        if dtype == 0x03:       # int
            return int(size)
        if dtype == 0x06:       # Date
            return time.localtime(size)
        if dtype == 0x30:       # Object[]
            return [ self._recv() for x in xrange(size) ]
        if dtype == 0x31:       # Map
            ret = {}
            for x in xrange(size):
                k = self._recv()
                ret[k] = self._recv()
            return ret
        while self._ptr + size > len(self._buf):
            self._recvMore()
        if dtype == 0x04 or dtype == 0x05:       # float or double
            ret = float(self._buf[self._ptr : self._ptr + size])
            self._ptr += size
            return ret
        if dtype == 0x07:       # long
            ret = long(self._buf[self._ptr : self._ptr + size])
            self._ptr += size
            return ret
        if dtype == 0x10:       # String
            ret = self._buf[self._ptr : self._ptr + size].decode('utf-8')  
            self._ptr += size
            return ret
        if dtype == 0x20:       # byte[]
            ret = self._buf[self._ptr : self._ptr + size]
            self._ptr += size
            return tuple(ord(x) for x in ret)
        raise Exception('data type invalid')   

    
    def _recvMore(self):
        data = self._sock.recv(Client.RECV_SIZE)
        if data is None or len(data) == 0:
            raise Exception('recv data error')
        self._buf += data
