local FruitItem = class("FruitItem", function(x, y, fruitIndex)
	fruitIndex = fruitIndex or math.round(math.random() * 1000) % 8 + 1
	local sprite = display.newSprite("#fruit"  .. fruitIndex .. '_1.png')
	sprite.fruitIndex = fruitIndex
	sprite.x = x
	sprite.y = y
	sprite.isActive = false
	return sprite
end)

local g_fruitWidth = 0

function FruitItem:ctor()
    --self:setTouch()
end

function FruitItem:getSelfIndex()
    if self.fruitIndex then
        return self.fruitIndex
    end
end

function FruitItem:setActive(active)
    self.isActive = active

    local frame
    if (active) then
        frame = display.newSpriteFrame("fruit"  .. self.fruitIndex .. '_2.png')
    else
        frame = display.newSpriteFrame("fruit"  .. self.fruitIndex .. '_1.png')
    end

    self:setSpriteFrame(frame)

    if (active) then
        self:stopAllActions()
        local scaleTo1 = cc.ScaleTo:create(0.1, 1.1)
        local scaleTo2 = cc.ScaleTo:create(0.05, 1.0)
        self:runAction(cc.Sequence:create(scaleTo1, scaleTo2))
    end
end

function FruitItem:containsTouchLocation(x, y)
    local pos = cc.p(self:getPosition())
    local position = self:convertToWorldSpace(cc.p(self:getPosition()))
    position = cc.p(self:getPosition())
    local s = self:getContentSize()

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

--function FruitItem:setTouch()
--    local function onMyTouchBegan( touch,event )
--        return true
--    end

--    local function onMyTouchEnded(touch, event)                
--        if self:containsTouchLocation(touch:getLocation().x, touch:getLocation().y) then
--		    if self.isActive then
--			    self:removeActivedFruits()
--			    self:dropFruits()
--		    else
--			    self:inactive()
--			    self:activeNeighbor(newFruit)
--			    self:showActivesScore()
--		    end
--        end
--    end

--    local touchListen = cc.EventListenerTouchOneByOne:create()
--    touchListen:registerScriptHandler(onMyTouchBegan, cc.Handler.EVENT_TOUCH_BEGAN)
--    touchListen:registerScriptHandler(onMyTouchEnded, cc.Handler.EVENT_TOUCH_ENDED)
--    local eventDispatcher = self:getEventDispatcher()
--    eventDispatcher:addEventListenerWithSceneGraphPriority(touchListen, self)
--end

function FruitItem.getWidth()
    g_fruitWidth = 0
    if (0 == g_fruitWidth) then
        local sprite = display.newSprite("#fruit1_1.png")
        g_fruitWidth = sprite:getContentSize().width
    end
    return g_fruitWidth
end

return FruitItem
