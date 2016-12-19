--region *.lua
--Date
--此文件由[BabeLua]插件自动生成

local TreePack= import("src.packages.treepack.TreePack")

--------------------------------
-- @function [parent=#] parseListWithInfoHead
-- @param binary data
-- @param head{struct,length=struct_length}
-- @param unit{struct,length=struct_length}
-- @return {headMap,unitList}
local function parseListWithInfoHead(data,head,unit)
	local headMap=TreePack.unpack(data,head.struct)

	local unitsData=data:sub(head.length+1)
	local function getUnit(index)
		if(index*unit.length>unitsData:len())then
			return nil
		end
		local unitData=unitsData:sub(unit.length*(index-1)+1,unit.length*index)
		local unitMap=TreePack.unpack(unitData,unit.struct)
		return unitMap
	end

	local unitsList={}
	local iter=0
	for unit in function() iter=iter+1;return getUnit(iter) end do
		table.insert(unitsList,unit)
	end

	return {headMap,unitsList}
end

local function  resolveReference(ss)
	local lengthMap,refered_struct
	for name,tstruct in pairs(ss) do
		lengthMap=tstruct.lengthMap
		for index,value in pairs(lengthMap) do
			if(type(value)=='table' 
				and value.complexType and value.complexType=='link_refer' 
				and type(value.refered)=='string'
			)then
				refered_struct=ss[value.refered]
				assert(refered_struct~=nil,'struct '..value.refered..' dosen\'t exist')
				value.refered=refered_struct
			end
		end
	end
end

local _M = {
	parseListWithInfoHead = parseListWithInfoHead,
	resolveReference=resolveReference,
}

return _M

--endregion
