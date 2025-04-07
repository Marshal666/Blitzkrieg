function NearSafeZone()
local A_Bombers = 19;
local A_GroundAttack = 36; 
local A_Fighters = 20;
local A_Scout = 21;
local A_Paradrop = 22;
		Cmd (A_Bombers, 10000, 1, 2000, 2000);
		Suicide();
end;

function NearSafeZone1()
local A_Bombers = 19;
local A_GroundAttack = 36; 
local A_Fighters = 20;
local A_Scout = 21;
local A_Paradrop = 22;
		Cmd (A_GroundAttack, 10000, 1, 2000, 2000);
		Suicide();
end;

function NearSafeZone2()
local A_Bombers = 19;
local A_GroundAttack = 36; 
local A_Fighters = 20;
local A_Scout = 21;
local A_Paradrop = 22;
		Cmd (A_Fighters, 10000, 1, 2000, 2000);
		Suicide();
end;

function NearSafeZone3()
local A_Bombers = 19;
local A_GroundAttack = 36; 
local A_Fighters = 20;
local A_Scout = 21;
local A_Paradrop = 22;
		Cmd (A_Scout, 10000, 1, 0, 1000, 1000, 200);
		Suicide();
end;

function NearSafeZone4()
local A_Bombers =19;
local A_GroundAttack = 36;
local A_Fighters = 20;
local A_Scout = 21;
local A_Paradrop = 22;
                Cmd (A_Paradrop, 10000, 1, 2000, 2000)        
function Init()
	RunScript( "NearSafeZone1", 1000);
	RunScript( "NearSafeZone2", 10000);
	RunScript( "NearSafeZone3", 20000);
	RunScript( "NearSafeZone4", 30000);
	RunScript( "NearSafeZone4", 40000);
end;