#pragma once

#include "Psybrus.h"
#include "GaModalComponent.h"
#include "System/Scene/ScnComponent.h"

#include "System/Scene/Rendering/ScnMaterial.h"

//////////////////////////////////////////////////////////////////////////
// GaGameEvents
#define GA_EVENTGROUP_FLOW		EVT_MAKE_ID( 'G', 'a', 0 )

////////////////////////////////////////////////////////////////////////////////
// Event enum
enum GsEvents
{
	// All core events.
	gaEVT_FLOW_FIRST = GA_EVENTGROUP_FLOW,
	gaEVT_FLOW_ACTION,
};

struct GaActionEvent : EvtEvent< GaActionEvent >
{
	BcName SourceName_;
	BcName SourceType_;
	BcName Target_;
};

//////////////////////////////////////////////////////////////////////////
// GaGameComponentRef
typedef ReObjectRef< class GaGameComponent > GaGameComponentRef;

//////////////////////////////////////////////////////////////////////////
// GaGameObject
struct GaGameObject
{
	REFLECTION_DECLARE_BASIC( GaGameObject );
	GaGameObject(){}
	std::string Object_; // Name as identifier ( {type}_{name} ) used for entity
	std::string Room_; // Name of the room they're in ( ROOM_{number} )
	std::string InfoText_; // Information returned by entity
	std::vector< std::string > Infos_; // What information is revealed ( {TYPE}_{NAME} )

	std::string Target_;
};

//////////////////////////////////////////////////////////////////////////
// GaSolutionObject
struct GaSolutionObject
{
	REFLECTION_DECLARE_BASIC( GaSolutionObject );
	GaSolutionObject(){}
	std::string Type_;
	std::string Name_;
	std::string MissingMessage_;
	std::string Question_;
};

//////////////////////////////////////////////////////////////////////////
// GaRoomObject
struct GaRoomObject
{
	REFLECTION_DECLARE_BASIC( GaRoomObject );
	GaRoomObject():
		Entity_( nullptr )
	{}
	class ScnEntity* Entity_;
	std::string Text_;
	std::vector< std::string > Verbs_;
};

//////////////////////////////////////////////////////////////////////////
// GaCharacterObject
struct GaCharacterObject
{
	REFLECTION_DECLARE_BASIC( GaCharacterObject );
	GaCharacterObject():
		Entity_( nullptr )
	{}
	class ScnEntity* Entity_;
	std::string Text_;
	std::vector< std::string > ValidNames_;
};

//////////////////////////////////////////////////////////////////////////
// GaGameComponent
class GaGameComponent:
	public ScnComponent
{
public:
	REFLECTION_DECLARE_DERIVED( GaGameComponent, ScnComponent );

	GaGameComponent();
	virtual ~GaGameComponent();
	
	virtual void onAttach( ScnEntityWeakRef Parent );
	virtual void onDetach( ScnEntityWeakRef Parent );

	void spawnRoom( const BcName& RoomName );
	void spawnModal( const BcName& ModalName, const BcName& Source );
	void spawnModal( const BcName& ModalName, const std::vector< GaModalOptionGroup >& OptionGroups );
	
	void useObject( const BcName& ObjectName );

	GaGameObject* findObject( const BcName& ObjectName );

	void onDoorEvent( const GaActionEvent& Event );
	void onPersonEvent( const GaActionEvent& Event );
	void onButlerEvent( const GaActionEvent& Event );

private:
	class ScnCanvasComponent* Canvas_;

	enum class GameState
	{
		IDLE,
		IN_MODAL_OBJECT,
		IN_MODAL_BUTLER,
		TRANSITION_OUT,
		TRANSITION_IN
	};

	GameState GameState_;
	ScnEntityRef CurrentRoomEntity_;
	ScnEntityRef ModalDialogEntity_;

	class ScnSound* Music_;
	
	std::vector< GaRoomObject > Rooms_;
	std::vector< GaCharacterObject > Characters_;

	// TODO: Use BcNames...
	std::string Room_;
	std::vector< GaGameObject > Objects_;
	std::set< std::string > Infos_;
	std::vector< GaSolutionObject > Solution_;
	BcU32 AttemptedSolutionObjects_;
	BcU32 CorrectSolutionObjects_;
	BcBool Guessing_;
	BcBool SetWin_;
	BcBool SetLose_;

	std::vector< std::string > CharacterNames_;

	
	std::map< std::string, std::string > IDTextMapping_;

	class ScnMaterialComponent* FontMaterial_;
	class ScnFont* Font_;
	class ScnFontComponent* FontComponent_;

};
