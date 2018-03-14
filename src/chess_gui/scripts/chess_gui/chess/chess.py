# -*- coding: utf-8 -*-



from ubsi import Client

class Chess:
    FEN_UP = 'rnbakcp'     
    FEN_DOWN = 'RNBAKCP'    
    TEXT_BLACK = (u"車", u"馬", u"象", u"士", u"将", u"砲", u"卒")
    TEXT_RED = (u"俥", u"傌", u"相", u"仕", u"帥", u"炮", u"兵")

    def __init__(self, host, port):
        self._uc = Client(host, port)
        self._save_board = None
        self._cur_board = None
        self._black_up = True



    def __del__(self):
        del self._uc

   
    def startBoard(self, board, black_up):

        [res] = self._uc.call('ai.chess.Server', 'startBoard', board, black_up)
        if res is None:
            self._cur_board = board
            self._black_up = black_up
        return res     

    def setBoard(self, board):
        [res] = self._uc.call('ai.chess.Server', 'setBoard', board)
        if len(res) > 0 and res[0] == '0':
            self._save_board = self._cur_board
            self._cur_board = board
        return res

   
    def thinkAndMove(self, up, draw=False):
        [res, board] = self._uc.call('ai.chess.Server', 'thinkAndMove', up, draw)
        if res:
            self._save_board = self._cur_board
            self._cur_board = board
        return res

   
    def moveStep(self, step, up):
        [res, board] = self._uc.call('ai.chess.Server', 'moveStep', step, up)
        if not res:
            self._save_board = self._cur_board
            self._cur_board = board
        return res

  
    def printBoard(self):
        _printBoard(self._save_board, self._cur_board, self._black_up)

def _printBoard(b1, b2, black_up):
    h = u'  ａ ｂ ｃ ｄ ｅ ｆ ｇ ｈ ｉ '
    if b1 and b2:
        h += u'　　ａ ｂ ｃ ｄ ｅ ｆ ｇ ｈ ｉ '
    print h

    if b1:
        b1 = b1.split('/')
    if b2:
        b2 = b2.split('/')

    for r in xrange(10):
        s = unicode(9-r) + ' '
        if b1:
            s += _getLine(b1[r], black_up)
        if b1 and b2:
            s += u'　　'
        if b2:
            s += _getLine(b2[r], black_up)
        s += u' ' + unicode(9-r)
        print s
    print h

def _getLine(ls, black_up):
    res = u''
    for c in ls:
        n = ord(c)
        if n >= ord('1') and n <= ord('9'):
            res += u'－ ' * (n - ord('0'))
        else:
            txt = Chess.TEXT_BLACK if black_up else Chess.TEXT_RED
            n = Chess.FEN_UP.find(c)
            if n < 0:
                txt = Chess.TEXT_RED if black_up else Chess.TEXT_BLACK
                n = Chess.FEN_DOWN.find(c)
            if n < 0:
                res += '*' + c + '*'
            else:
                res += txt[n] + ' '
    return res
