/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */

#ifndef GAME_CLIENT_COMPONENTS_TEXTURES_H
#define GAME_CLIENT_COMPONENTS_TEXTURES_H

#include <game/client/component.h>
#include <game/client/ui.h>

class CTextures : public CComponent
{
private:
    void ReloadEmoticons();
    void ReloadGui();
    void ReloadHud();
    void ReloadMapItems();
    void ReloadParticles();
    void ReloadWeapons();

public:
    CTextures();
	virtual int Sizeof() const override { return sizeof(*this); }

	virtual void OnInit() override;
    
	void RenderCursor(vec2 Center, float Size) const;

    // emoticons
    IGraphics::CTextureHandle m_aEmoticonTextures[NUM_EMOTICONS];
	IGraphics::CTextureHandle CTextures::EmoticonTexture(int Index);

    // static const char *const s_aEmoticonTexturePaths[NUM_EMOTICONS];

    // gui
    enum EGuiTextures
	{
        GUI_AUDIO_SOURCE,
        GUI_BACKGROUND,
        GUI_CHECKER,
        GUI_CONSOLE,
        GUI_CONSOLE_BAR,
        GUI_CURSOR_MAIN,
        GUI_CURSOR_EDITOR,
        GUI_CURSOR_RESIZE,
        GUI_LOGO,
        GUI_BUTTON_HOVER,
        GUI_BUTTON_OFF,
        GUI_BUTTON_ON,
        GUI_ICON_EMOTICON_MUTE,
        GUI_ICON_FRIEND,
        GUI_ICON_MUTE,
        GUI_SPEED_ARROW,
        NUM_GUI_TEXTURES
	};
	IGraphics::CTextureHandle m_aGuiTextures[EGuiTextures::NUM_GUI_TEXTURES];
	EGuiTextures m_GuiTextures;
    IGraphics::CTextureHandle CTextures::GuiTexture(int Index);

    // hud
    enum EHudTextures
	{
        HUD_AIRJUMP_EMPTY,
        HUD_AIRJUMP_FULL,
        HUD_ARMOR_EMPTY,
        HUD_ARMOR_FULL,
        HUD_ARROW,
        HUD_HEALTH_EMPTY,
        HUD_HEALTH_FULL,
        HUD_COLLISION_DISABLED,
        HUD_DEEP_FROZEN,
        HUD_LIVE_FROZEN,
        HUD_DUMMY_COPY,
        HUD_DUMMY_HAMMER,
        HUD_ENDLESS_HOOK,
        HUD_ENDLESS_JUMP,
        HUD_FREEZE_BAR_EMPTY,
        HUD_FREEZE_BAR_EMPTY_RIGHT,
        HUD_FREEZE_BAR_FULL,
        HUD_FREEZE_BAR_FULL_LEFT,
        HUD_GUN_HIT_DISABLED,
        HUD_HOOK_HIT_DISABLED,
        HUD_HAMMER_HIT_DISABLED,
        HUD_SHOTGUN_HIT_DISABLED,
        HUD_GRENADE_HIT_DISABLED,
        HUD_LASER_HIT_DISABLED,
        HUD_JETPACK,
        HUD_NINJA_BAR_EMPTY,
        HUD_NINJA_BAR_EMPTY_RIGHT,
        HUD_NINJA_BAR_FULL,
        HUD_NINJA_BAR_FULL_LEFT,
        HUD_PRACTICE_MODE,
        HUD_SOLO,
        HUD_TELEPORT_GRENADE,
        HUD_TELEPORT_GUN,
        HUD_TELEPORT_LASER,
        HUD_STRONG_HOOK,
        HUD_WEAK_HOOK,
        HUD_LOCK_MODE,
        HUD_TEAM_0_MODE,
        HUD_RACE_FLAG,
        NUM_HUD_TEXTURES
	};
	IGraphics::CTextureHandle m_aHudTextures[EHudTextures::NUM_HUD_TEXTURES];
	EHudTextures m_HudTextures;
    IGraphics::CTextureHandle CTextures::HudTexture(int Index);

    // map items
    enum EMapItemTextures
	{
        MAPITEM_FLAG_BLUE,
        MAPITEM_FLAG_RED,
        MAPITEM_PICKUP_ARMOR,
        MAPITEM_PICKUP_ARMOR_GRENADE,
        MAPITEM_PICKUP_ARMOR_LASER,
        MAPITEM_PICKUP_ARMOR_NINJA,
        MAPITEM_PICKUP_ARMOR_SHOTGUN,
        MAPITEM_PICKUP_HEALTH,
        MAPITEM_PICKUP_MISC,
        NUM_MAPITEM_TEXTURES
	};
	IGraphics::CTextureHandle m_aMapItemTextures[EMapItemTextures::NUM_MAPITEM_TEXTURES];
    IGraphics::CTextureHandle m_aMapItemPickupArmors[4];
	EMapItemTextures m_MapItemTextures;
    IGraphics::CTextureHandle CTextures::MapItemTexture(int Index);

    // particles
    enum EParticleTextures
	{
        PARTICLE_AIR_JUMP,
        PARTICLE_BALL,
        PARTICLE_EXPLOSION_1,
        PARTICLE_HIT_01,
        PARTICLE_SHELL,
        PARTICLE_SLICE,
        PARTICLE_SMOKE,
        PARTICLE_SNOWFLAKE,
        PARTICLE_SPLAT_1,
        PARTICLE_SPLAT_2,
        PARTICLE_SPLAT_3,
        PARTICLE_MISC_1,
        PARTICLE_MISC_2,
        PARTICLE_MISC_3,
        PARTICLE_MISC_4,
        PARTICLE_MISC_5,
        PARTICLE_MISC_6,
        PARTICLE_MISC_7,
        PARTICLE_MISC_8,
        PARTICLE_MISC_9,
        PARTICLE_SPARKLE,
        PARTICLE_STAR_1,
        PARTICLE_STAR_2,
        PARTICLE_STAR_3,
		NUM_PARTICLE_TEXTURES
	};
	IGraphics::CTextureHandle m_aParticleTextures[EParticleTextures::NUM_PARTICLE_TEXTURES];
    IGraphics::CTextureHandle m_aParticleSplats[3];
	EParticleTextures m_ParticleTextures;
    IGraphics::CTextureHandle CTextures::ParticleTexture(int Index);


    // weapons
    enum EWeaponTextures
	{
		WEAPON_HOOK_CHAIN,
		WEAPON_HOOK_HEAD,
		WEAPON_HAMMER_BODY,
		WEAPON_HAMMER_CURSOR,
		WEAPON_GUN_BODY,
		WEAPON_GUN_CURSOR,
		WEAPON_GUN_PROJ,
		WEAPON_GUN_MUZZLE_1,
		WEAPON_GUN_MUZZLE_2,
		WEAPON_GUN_MUZZLE_3,
		WEAPON_SHOTGUN_BODY,
		WEAPON_SHOTGUN_CURSOR,
		WEAPON_SHOTGUN_PROJ,
		WEAPON_SHOTGUN_MUZZLE_1,
		WEAPON_SHOTGUN_MUZZLE_2,
		WEAPON_SHOTGUN_MUZZLE_3,
		WEAPON_GRENADE_BODY,
		WEAPON_GRENADE_CURSOR,
		WEAPON_GRENADE_PROJ,
		WEAPON_LASER_BODY,
		WEAPON_LASER_CURSOR,
		WEAPON_LASER_PROJ,
		WEAPON_NINJA_BODY,
		WEAPON_NINJA_CURSOR,
		WEAPON_NINJA_MUZZLE_1,
		WEAPON_NINJA_MUZZLE_2,
		WEAPON_NINJA_MUZZLE_3,
		NUM_WEAPON_TEXTURES
	};
	IGraphics::CTextureHandle m_aWeaponTextures[EWeaponTextures::NUM_WEAPON_TEXTURES];
    IGraphics::CTextureHandle m_aWeaponBodies[NUM_WEAPONS];
    IGraphics::CTextureHandle m_aWeaponCursors[NUM_WEAPONS];
    IGraphics::CTextureHandle m_aWeaponProjectiles[NUM_WEAPONS];
    IGraphics::CTextureHandle m_aWeaponGunMuzzles[3];
    IGraphics::CTextureHandle m_aWeaponShotgunMuzzles[3];
    IGraphics::CTextureHandle m_aWeaponNinjaMuzzles[3];
    IGraphics::CTextureHandle m_aaWeaponMuzzles[NUM_WEAPONS][3];
	EWeaponTextures m_WeaponTextures;
    IGraphics::CTextureHandle CTextures::WeaponTexture(int Index);
};

#endif // GAME_CLIENT_COMPONENTS_TEXTURES_H