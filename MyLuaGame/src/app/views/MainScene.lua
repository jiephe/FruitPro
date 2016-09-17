
local MainScene = class("MainScene", cc.load("mvc").ViewBase)

function MainScene:onCreate()
	-- 1.加载精灵帧
    display.loadSpriteFrames("fruit.plist", "fruit.png")

    -- 2.背景图片
	display.newSprite("mainBG.png")
		:move(display.center)
		:addTo(self)

       --1. 加载正常的图片
--    local function  touchEvent()
--		local playScene = import("app.views.PlayScene"):new()
--		display.replaceScene(playScene, "turnOffTiles", 0.5)  
--    end
--    local button = ccui.Button:create()
--    button:setTouchEnabled(true)
--    button:loadTexture("animationbuttonnormal.png", "animationbuttonpressed.png", "')
--    button:setAnchorPoint(cc.p(0.5, 0.5))
--    button:setPosition(cc.p(display.cx, display.cy-200))
--    button:addClickEventListener(touchEvent)
--    self:addChild(button)

    --2. 加载plist里的图片
    local function menuCallback(tag, menuItem)
		local playScene = import("app.views.PlayScene"):new()			
        local director=cc.Director:getInstance()
		if director:getRunningScene() then
			director:replaceScene(playScene)
		end

		--display.replaceScene(playScene, "turnOffTiles", 0.5) 
    end

    local menu = cc.Menu:create()
    menu:setAnchorPoint(cc.p(0.5, 0.5))
    menu:setPosition(cc.p(0, 0))
    self:addChild(menu)
    local menuItem = cc.MenuItemSprite:create(display.newSprite("#startBtn_N.png"), 
                                                display.newSprite("#startBtn_N.png"), 
                                                display.newSprite("#startBtn_N.png"))

    menu:addChild(menuItem)
    menuItem:setAnchorPoint(cc.p(0.5, 0.5))
    menuItem:setPosition(cc.p(display.cx, display.cy-200))
    menuItem:registerScriptTapHandler(menuCallback)
end

return MainScene
