
cc.FileUtils:getInstance():setPopupNotify(false)
cc.FileUtils:getInstance():addSearchPath("src/")
cc.FileUtils:getInstance():addSearchPath("res/")

require "config"
require "cocos.init"

local treepack          = cc.load("treepack")

cc.exports.testVar = 10000
cc.exports.testStr = "hello world!"

local AUCTION_BANKER_AUTO={
	lengthMap = {
		[7] = {maxlen = 4},
		maxlen = 7
	},
	nameMap = {
		'nUserID',
		'nRoomID',
		'nTableNO',
		'nChairNO',
		'nAutoChairNO',
		'nGains',
		'nReserved'
	},
	formatKey = '<iiiiiiiiii',
	deformatKey = '<iiiiiiiiii',
	maxsize = 40
}

local function testet(nInt, str, data)
    local info = treepack.unpack(data, AUCTION_BANKER_AUTO)
    local a = info.nChairNO
    local b = info.nAutoChairNO

    return 123456
end

local function main()
    local test = MyClass:create()

    local data          = 
    {
        nUserID         = 100,
        nRoomID         = 100,
        nTableNO        = 100,
        nChairNO        = 100,
        nAutoChairNO    = 200,
        nGains          = 0
    }
    local pData = treepack.alignpack(data, AUCTION_BANKER_AUTO)
    local b = test.TransmitLuaContruct

    test:TransmitLuaContructWithCallBack(testet)

    require("app.MyApp"):create():run()
end

local status, msg = xpcall(main, __G__TRACKBACK__)
if not status then
    print(msg)
end
