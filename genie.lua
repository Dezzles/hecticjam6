
-- Run psybrus scripts.
psybrusSDK = "Psybrus"
dofile( "Psybrus/Scripts/Psybrus.lua" )


-- Solution.
PsySolutionGame( "HecticJam6" )

-- Build externals.
dofile ("Psybrus/External/genie.lua")

-- Build engine.
dofile ("Psybrus/Engine/genie.lua")

-- Build game source.
dofile ("./Source/genie.lua")

