local args = {...}
local vs  = args[1]
local depsDir = args[2]
local vsBuildCommon = "/verbosity:minimal /t:Build /toolsversion:".. vs.toolVersion .." /p:Platform=x64 /p:VisualStudioVersion=".. vs.toolVersion .." /p:WindowsTargetPlatformVersion=".. vs.sdkVersion

local PACKAGES = {}

local function moveFile(fromFolder, toFolder, fileName)
	os.mkdir(toFolder)
	local succ, err = os.rename(fromFolder .. fileName, toFolder .. fileName)
	
	if not succ then
		print(err)
	end
end

local function moveFolder(from, to)
	local temp = "_TEMP_".. math.random(0, 10000) .."_/"
	
	local succ, err = os.rename(from, temp)
	if succ then
		os.rmdir(from)
		os.mkdir(to)
		os.rmdir(to)
		
		succ, err = os.rename(temp, to)
		
		if not succ then
			print(err)
		end
	else
		print(err)
	end
end

local function buildMSBuild(fileName, args)
	io.write("\n")
	os.execute(vs.msbuild .." ".. fileName .." ".. vsBuildCommon .." ".. args)
end

local function buildCMakeProjectWithMSBuild(workingDir, buildDir, buildFile, cmakeArgs, msBuildArgs, filesToMove)
	local oldDir = os.getcwd()
	
	os.mkdir(workingDir .. buildDir)
	os.chdir(workingDir .. buildDir)
	
	-- CMake
	io.write("\n")
	os.execute(
		'cmake -G "'.. vs.cmake ..'" '..
		table.concat(cmakeArgs, " ") ..
		' ..'
	)
	
	-- MSBuild
	local buildCommon = table.concat(msBuildArgs, " ") .." ".. vsBuildCommon
	
	buildMSBuild(buildFile, buildCommon .." /p:Configuration=Debug")
	buildMSBuild(buildFile, buildCommon .." /p:Configuration=Release")
	
	-- Move files
	os.chdir(oldDir .. workingDir)
	
	for k,v in pairs(filesToMove) do
		moveFile(table.unpack(v))
	end
	
	os.chdir(oldDir)
end

--------------------------------------------------------------------------------
-- Packages
--------------------------------------------------------------------------------
PACKAGES["googletest"] = {
	name = "Google Test",
	url = "https://github.com/google/googletest/archive/master.zip",

	postExtract = function(uid)
		local dir = depsDir .. uid .."/"
		moveFolder(dir .."googletest-master/", dir)
	end,
	
	build = function(uid)
		local dir =  depsDir .. uid .."/"
		local cmakeCommon = {"-Dgtest_force_shared_crt=ON"}
		
		if os.target() == "windows" then
			buildCMakeProjectWithMSBuild(dir, "googletest/build/", "gtest.sln", cmakeCommon, {}, {
				{"./googletest/build/Debug/", "./lib/debug/", "gtestd.lib"},
				{"./googletest/build/Release/", "./lib/release/", "gtest.lib"},
			})
			
			buildCMakeProjectWithMSBuild(dir, "googlemock/build/", "gmock.sln", cmakeCommon, {}, {
				{"./googlemock/build/Debug/", "./lib/debug/", "gmockd.lib"},
				{"./googlemock/build/Release/", "./lib/release/", "gmock.lib"},
			})
		else
			-- TODO: 
			io.write("ERROR: TODO: Configure non-windows builds")
		end
	end,
}

return PACKAGES
 