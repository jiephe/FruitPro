local FruitItem = import("app.views.FruitItem")

local PlayScene = class("PlayScene", function()
	return display.newScene("PlayScene")
end)

function PlayScene:ctor()
	-- init value
	self.highSorce = 0 -- 最高分数
	self.stage = 1 -- 当前关卡
	self.target = 123 -- 通关分数
	self.curSorce = 0 -- 当前分数
	self.xCount = 8 -- 水平方向水果数
	self.yCount = 8 -- 垂直方向水果数
	self.fruitGap = 0 -- 水果间距
	self.scoreStart = 5 -- 水果基分
	self.scoreStep = 10 -- 加成分数
	self.activeScore = 0 -- 当前高亮的水果得分

	self:initUI()

	-- 初始化随机数
	--math.newrandomseed()

	--  计算水果矩阵左下角的x、y坐标：以矩阵中点对齐屏幕中点来计算，然后再做Y轴修正。
	self.matrixLBX = (display.width - FruitItem.getWidth() * self.xCount - (self.yCount - 1) * self.fruitGap) / 2
	self.matrixLBY = (display.height - FruitItem.getWidth() * self.yCount - (self.xCount - 1) * self.fruitGap) / 2 - 30

	-- 等待转场特效结束后再加载矩阵
--	self:addNodeEventListener(cc.NODE_EVENT, function(event)
--		if event.name == "enterTransitionFinish" then
--			self:initMartix()
--		end
--	end)

    self:initMartix()
end

function PlayScene:initUI()
	-- 背景图片
	display.newSprite("playBG.png")
		:move(display.center)
		:addTo(self)

    local function menuCallback(tag, menuItem)
	    local mainScene = import("app.views.MainScene"):new()	
        local newScene = cc.Scene:create()
        mainScene:addTo(newScene) 	
		local director=cc.Director:getInstance()
		if director:getRunningScene() then
			director:replaceScene(newScene)
		else
			director:runWithScene(newScene)
		end
    end

    local menu = cc.Menu:create()
    menu:setAnchorPoint(cc.p(0.5, 0.5))
    menu:setPosition(cc.p(0, 0))
    self:addChild(menu, 1)
    local menuItem = cc.MenuItemSprite:create(display.newSprite("#startBtn_N.png"), 
                                                display.newSprite("#startBtn_N.png"), 
                                                display.newSprite("#startBtn_N.png"))

    menu:addChild(menuItem)
    menuItem:setAnchorPoint(cc.p(0.5, 0.5))
    menuItem:setPosition(cc.p(display.cx, display.cy-450))
    menuItem:registerScriptTapHandler(menuCallback)


	-- high sorce
	display.newSprite("#high_score.png")
		:align(display.LEFT_CENTER, display.left + 15, display.top - 30)
		:addTo(self)

	display.newSprite("#highscore_part.png")
		:align(display.LEFT_CENTER, display.cx + 10, display.top - 26)
		:addTo(self)
        
    self.highSorceLabel = cc.LabelBMFont:create("0", "font/earth38.fnt")
	--self.highSorceLabel = cc.ui.UILabel.new({UILabelType = 1, text = tostring(self.highSorce), font = "font/earth38.fnt"})
	self.highSorceLabel:setString(tostring(self.highSorce))
    self.highSorceLabel:align(display.CENTER, display.cx + 105, display.top - 24)
	self.highSorceLabel:addTo(self)
	
	-- 声音
	display.newSprite("#sound.png")
		:align(display.CENTER, display.right - 60, display.top - 30)
		:addTo(self)

	-- stage
	display.newSprite("#stage.png")
		:align(display.LEFT_CENTER, display.left + 15, display.top - 80)
		:addTo(self)

	display.newSprite("#stage_part.png")
		:align(display.LEFT_CENTER, display.left + 170, display.top - 80)
		:addTo(self)

    self.highStageLabel = cc.LabelBMFont:create("0", "font/earth32.fnt")
	--self.highStageLabel = cc.ui.UILabel.new({UILabelType = 1, text = tostring(self.stage), font = "font/earth32.fnt"})
	self.highStageLabel:setString(tostring(self.stage))
    self.highStageLabel:align(display.CENTER, display.left + 214, display.top - 78)
    self.highStageLabel:addTo(self)
	
	-- target
	display.newSprite("#tarcet.png")
		:align(display.LEFT_CENTER, display.cx - 50, display.top - 80)
		:addTo(self)

	display.newSprite("#tarcet_part.png")
		:align(display.LEFT_CENTER, display.cx + 130, display.top - 78)
		:addTo(self)

    self.highTargetLabel = cc.LabelBMFont:create("0", "font/earth32.fnt")
	--self.highTargetLabel = cc.ui.UILabel.new({UILabelType = 1, text = tostring(self.target), font = "font/earth32.fnt"})
	self.highTargetLabel:setString(tostring(self.target))
    self.highTargetLabel:align(display.CENTER, display.cx + 195, display.top - 76)
    self.highTargetLabel:addTo(self)

	-- current sorce
	display.newSprite("#score_now.png")
		:align(display.CENTER, display.cx, display.top - 150)
		:addTo(self)

    self.curSorceLabel = cc.LabelBMFont:create("0", "font/earth48.fnt")
	--self.curSorceLabel = cc.ui.UILabel.new({UILabelType = 1, text = tostring(self.curSorce), font = "font/earth48.fnt"})
    self.curSorceLabel:setString(tostring(self.curSorce))
    self.curSorceLabel:align(display.CENTER, display.cx, display.top - 150)
    self.curSorceLabel:addTo(self)
	
	-- 选中水果分数
    self.activeScoreLabel = cc.LabelTTF:create()
    self.activeScoreLabel:setFontSize(30) 
	--self.activeScoreLabel = display.newTTFLabel({text = "", size = 30})
		self.activeScoreLabel:setPosition(cc.p(display.width / 2, 120))
		self.activeScoreLabel:addTo(self)
	self.activeScoreLabel:setColor(display.COLOR_WHITE)
end

function PlayScene:initMartix()
	-- 创建空矩阵
	self.matrix = {}
	-- 高亮水果
	self.actives = {}
	for y = 1, self.yCount do
		for x = 1, self.xCount do
			if 1 == y and 2 == x then
                -- 确保有可消除的水果
                self:createAndDropFruit(x, y, self.matrix[1].fruitIndex)
            else 
                self:createAndDropFruit(x, y)
			end
		end
	end
end

function PlayScene:containsTouchLocation(item, x, y)
    local pos = cc.p(item:getPosition())
    local position = item:convertToWorldSpace(cc.p(item:getPosition()))
    position = cc.p(item:getPosition())
    local s = item:getContentSize()

    local touchRect

--    if self:isSelectCard() then --and self._bTouched then
--        touchRect = cc.rect(position.x, position.y - self._MJOffsetY, s.width, s.height + self._MJOffsetY)
--    else
--        touchRect = cc.rect(position.x, position.y, s.width, s.height)
--    end

    touchRect = cc.rect(position.x, position.y, s.width, s.height)

    local b = cc.rectContainsPoint(touchRect, cc.p(x, y))
    return b
end

function PlayScene:createAndDropFruit(x, y, fruitIndex)
    local newFruit = FruitItem.new(x, y, fruitIndex)
    local endPosition = self:positionOfFruit(x, y)
    local startPosition = cc.p(endPosition.x, endPosition.y + display.height / 2)
    newFruit:setPosition(startPosition)
    local speed = startPosition.y / (2 * display.height)
    newFruit:runAction(cc.MoveTo:create(speed, endPosition))
    self.matrix[(y - 1) * self.xCount + x] = newFruit
    self:addChild(newFruit)

	-- 绑定触摸事件
    local function onMyTouchBegan( touch,event )
        return true
    end

    local function onMyTouchEnded(touch, event)                
        if self:containsTouchLocation(newFruit, touch:getLocation().x, touch:getLocation().y) then
		    if newFruit.isActive then
			    self:removeActivedFruits()
			    self:dropFruits()
		    else
			    self:inactive()
			    self:activeNeighbor(newFruit)
			    self:showActivesScore()
		    end
        end
        return true
    end

    local touchListen = cc.EventListenerTouchOneByOne:create()
    touchListen:registerScriptHandler(onMyTouchBegan, cc.Handler.EVENT_TOUCH_BEGAN)
    touchListen:registerScriptHandler(onMyTouchEnded, cc.Handler.EVENT_TOUCH_ENDED)
    local eventDispatcher = newFruit:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(touchListen, newFruit)
end

function PlayScene:removeActivedFruits()
	local fruitScore = self.scoreStart
	for _, fruit in pairs(self.actives) do
		if (fruit) then
			-- 从矩阵中移除
			self.matrix[(fruit.y - 1) * self.xCount + fruit.x] = nil
			-- 分数特效
			self:scorePopupEffect(fruitScore, fruit:getPosition())
			fruitScore = fruitScore + self.scoreStep
			fruit:removeFromParent()
		end
	end

	-- 清空高亮数组
	self.actives = {}

	-- 更新当前得分
	self.curSorce = self.curSorce + self.activeScore
	self.curSorceLabel:setString(tostring(self.curSorce))

	-- 清空高亮水果分数统计
	self.activeScoreLabel:setString("")
	self.activeScore = 0
end

function PlayScene:scorePopupEffect(score, px, py)
    local labelScore = cc.LabelBMFont:create("0", "font/earth32.fnt")
    labelScore:setString(tostring(score))
	--local labelScore = cc.ui.UILabel.new({UILabelType = 1, text = tostring(score), font = "font/earth32.fnt"})

	local move = cc.MoveBy:create(0.8, cc.p(0, 80))
	local fadeOut = cc.FadeOut:create(0.8)
	local action = transition.sequence({
		cc.Spawn:create(move,fadeOut),
		-- 动画结束移除 Label
		cc.CallFunc:create(function() labelScore:removeFromParent() end)
	})

	labelScore:setPosition(cc.p(px, py))
	labelScore:addTo(self)
	labelScore:runAction(action)
end

function PlayScene:dropFruits()
	local emptyInfo = {}

	-- 1. 掉落已存在的水果
	-- 一列一列的处理
	for x = 1, self.xCount do
		local removedFruits = 0
		local newY = 0
		-- 从下往上处理
		for y = 1, self.yCount do
			local temp = self.matrix[(y - 1) * self.xCount + x]
			if temp == nil then
				-- 水果已被移除
				removedFruits = removedFruits + 1
			else
				-- 如果水果下有空缺，向下移动空缺个位置
				if removedFruits > 0 then
					newY = y - removedFruits
					self.matrix[(newY - 1) * self.xCount + x] = temp
					temp.y = newY
					self.matrix[(y - 1) * self.xCount + x] = nil

					local endPosition = self:positionOfFruit(x, newY)
					local speed = (temp:getPositionY() - endPosition.y) / display.height
					temp:stopAllActions() --停止之前的动画
					temp:runAction(cc.MoveTo:create(speed, endPosition))
				end
			end
		end

		-- 纪录本列最终空缺数
		emptyInfo[x] = removedFruits
	end

	-- 2. 掉落新水果补齐空缺
	for x = 1, self.xCount do
		for y = self.yCount - emptyInfo[x] + 1, self.yCount do
			self:createAndDropFruit(x, y)
		end
	end
end

function PlayScene:positionOfFruit(x, y)
    local px = self.matrixLBX + (FruitItem.getWidth() + self.fruitGap) * (x - 1) + FruitItem.getWidth() / 2
    local py = self.matrixLBY + (FruitItem.getWidth() + self.fruitGap) * (y - 1) + FruitItem.getWidth() / 2
    return cc.p(px, py)
end

function PlayScene:activeNeighbor(fruit)
	-- 高亮fruit
	if false == fruit.isActive then
		fruit:setActive(true)
		table.insert(self.actives, fruit)
	end

	-- 检查fruit左边的水果
	if (fruit.x - 1) >= 1 then
		local leftNeighbor = self.matrix[(fruit.y - 1) * self.xCount + fruit.x - 1]
		if (leftNeighbor.isActive == false) and (leftNeighbor.fruitIndex == fruit.fruitIndex) then
			leftNeighbor:setActive(true)
			table.insert(self.actives, leftNeighbor)
			self:activeNeighbor(leftNeighbor)
		end
	end

	-- 检查fruit右边的水果
	if (fruit.x + 1) <= self.xCount then
		local rightNeighbor = self.matrix[(fruit.y - 1) * self.xCount + fruit.x + 1]
		if (rightNeighbor.isActive == false) and (rightNeighbor.fruitIndex == fruit.fruitIndex) then
			rightNeighbor:setActive(true)
			table.insert(self.actives, rightNeighbor)
			self:activeNeighbor(rightNeighbor)
		end
	end

	-- 检查fruit上边的水果
	if (fruit.y + 1) <= self.yCount then
		local upNeighbor = self.matrix[fruit.y * self.xCount + fruit.x]
		if (upNeighbor.isActive == false) and (upNeighbor.fruitIndex == fruit.fruitIndex) then
			upNeighbor:setActive(true)
			table.insert(self.actives, upNeighbor)
			self:activeNeighbor(upNeighbor)
		end
	end

	-- 检查fruit下边的水果
	if (fruit.y - 1) >= 1 then
		local downNeighbor = self.matrix[(fruit.y - 2) * self.xCount + fruit.x]
		if (downNeighbor.isActive == false) and (downNeighbor.fruitIndex == fruit.fruitIndex) then
			downNeighbor:setActive(true)
			table.insert(self.actives, downNeighbor)
			self:activeNeighbor(downNeighbor)
		end
	end
end

function PlayScene:inactive()
    for _, fruit in pairs(self.actives) do
        if (fruit) then
            fruit:setActive(false)
        end
    end
	self.actives = {}
end

function PlayScene:showActivesScore()
	-- 只有一个高亮，取消高亮并返回
	if 1 == #self.actives then
		self:inactive()
		self.activeScoreLabel:setString("")
		self.activeScore = 0
		return
	end

	-- 水果分数依次为5、15、25、35... ，求它们的和
	self.activeScore = (self.scoreStart * 2 + self.scoreStep * (#self.actives - 1)) * #self.actives / 2
	self.activeScoreLabel:setString(string.format("%d 连消，得分 %d", #self.actives, self.activeScore))
end

function PlayScene:onEnter()
end

function PlayScene:onExit()
end

return PlayScene
