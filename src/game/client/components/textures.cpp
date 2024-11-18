/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */

#include <engine/graphics.h>
#include <engine/shared/config.h>
#include <game/generated/protocol.h>

#include <base/log.h>
#include <game/client/gameclient.h>

#include "textures.h"

void CTextures::OnInit()
{
    ReloadEmoticons();
    ReloadGui();
    ReloadHud();
    ReloadMapItems();
    ReloadParticles();
    ReloadWeapons();

    log_info("textures", "Successfully loaded textures");
}

CTextures::CTextures()
{

}


void CTextures::RenderCursor(vec2 Center, float Size) const
{
	Graphics()->WrapClamp();
	Graphics()->TextureSet(m_aGuiTextures[GUI_CURSOR_MAIN]);
	Graphics()->QuadsBegin();
	Graphics()->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	IGraphics::CQuadItem QuadItem(Center.x, Center.y, Size, Size);
	Graphics()->QuadsDrawTL(&QuadItem, 1);
	Graphics()->QuadsEnd();
	Graphics()->WrapNormal();
}

void CTextures::ReloadEmoticons()
{
    try
	{
		for(auto &EmoticonTexture : m_aEmoticonTextures)
		{
			if(EmoticonTexture.IsValid())
				Graphics()->UnloadTexture(&EmoticonTexture);
		}
        /*
        for(int i = 0; i < NUM_EMOTICONS; i++)
        {
            m_aEmoticonTextures[i] = Graphics()->LoadTexture(s_aEmoticonTexturePaths[i], IStorage::TYPE_ALL)
        }
        */
		m_aEmoticonTextures[EMOTICON_OOP] = Graphics()->LoadTexture("images/emoticons/oop.png", IStorage::TYPE_ALL);
		m_aEmoticonTextures[EMOTICON_EXCLAMATION] = Graphics()->LoadTexture("images/emoticons/exclamation.png", IStorage::TYPE_ALL);
		m_aEmoticonTextures[EMOTICON_HEARTS] = Graphics()->LoadTexture("images/emoticons/hearts.png", IStorage::TYPE_ALL);
		m_aEmoticonTextures[EMOTICON_DROP] = Graphics()->LoadTexture("images/emoticons/drop.png", IStorage::TYPE_ALL);
		m_aEmoticonTextures[EMOTICON_DOTDOT] = Graphics()->LoadTexture("images/emoticons/dotdot.png", IStorage::TYPE_ALL);
		m_aEmoticonTextures[EMOTICON_MUSIC] = Graphics()->LoadTexture("images/emoticons/music.png", IStorage::TYPE_ALL);
		m_aEmoticonTextures[EMOTICON_SORRY] = Graphics()->LoadTexture("images/emoticons/sorry.png", IStorage::TYPE_ALL);
		m_aEmoticonTextures[EMOTICON_GHOST] = Graphics()->LoadTexture("images/emoticons/ghost.png", IStorage::TYPE_ALL);
		m_aEmoticonTextures[EMOTICON_SUSHI] = Graphics()->LoadTexture("images/emoticons/sushi.png", IStorage::TYPE_ALL);
		m_aEmoticonTextures[EMOTICON_SPLATTEE] = Graphics()->LoadTexture("images/emoticons/splattee.png", IStorage::TYPE_ALL);
		m_aEmoticonTextures[EMOTICON_DEVILTEE] = Graphics()->LoadTexture("images/emoticons/deviltee.png", IStorage::TYPE_ALL);
		m_aEmoticonTextures[EMOTICON_ZOMG] = Graphics()->LoadTexture("images/emoticons/zomg.png", IStorage::TYPE_ALL);
		m_aEmoticonTextures[EMOTICON_ZZZ] = Graphics()->LoadTexture("images/emoticons/zzz.png", IStorage::TYPE_ALL);
		m_aEmoticonTextures[EMOTICON_WTF] = Graphics()->LoadTexture("images/emoticons/wtf.png", IStorage::TYPE_ALL);
		m_aEmoticonTextures[EMOTICON_EYES] = Graphics()->LoadTexture("images/emoticons/eyes.png", IStorage::TYPE_ALL);
		m_aEmoticonTextures[EMOTICON_QUESTION] = Graphics()->LoadTexture("images/emoticons/question.png", IStorage::TYPE_ALL);
	}
	catch(const std::exception &e)
	{
		log_error("emoticon", "Failed to load emoticon textures: %s", e.what());
	}
}

void CTextures::ReloadGui()
{
    try
    {
        for(auto &GuiTexture : m_aGuiTextures)
        {
            if(GuiTexture.IsValid())
                Graphics()->UnloadTexture(&GuiTexture);
        }

        m_aGuiTextures[GUI_AUDIO_SOURCE] = Graphics()->LoadTexture("images/gui/audio_source.png", IStorage::TYPE_ALL);
        m_aGuiTextures[GUI_BACKGROUND] = Graphics()->LoadTexture("images/gui/background.png", IStorage::TYPE_ALL);
        m_aGuiTextures[GUI_CHECKER] = Graphics()->LoadTexture("images/gui/checker.png", IStorage::TYPE_ALL);
        m_aGuiTextures[GUI_CONSOLE] = Graphics()->LoadTexture("images/gui/console.png", IStorage::TYPE_ALL);
        m_aGuiTextures[GUI_CONSOLE_BAR] = Graphics()->LoadTexture("images/gui/console_bar.png", IStorage::TYPE_ALL);
        m_aGuiTextures[GUI_CURSOR_MAIN] = Graphics()->LoadTexture("images/gui/cursor_main.png", IStorage::TYPE_ALL);
        m_aGuiTextures[GUI_CURSOR_EDITOR] = Graphics()->LoadTexture("images/gui/cursor_editor.png", IStorage::TYPE_ALL);
        m_aGuiTextures[GUI_CURSOR_RESIZE] = Graphics()->LoadTexture("images/gui/cursor_resize.png", IStorage::TYPE_ALL);
        m_aGuiTextures[GUI_LOGO] = Graphics()->LoadTexture("images/gui/logo.png", IStorage::TYPE_ALL);
        m_aGuiTextures[GUI_BUTTON_HOVER] = Graphics()->LoadTexture("images/gui/button_hover.png", IStorage::TYPE_ALL);
        m_aGuiTextures[GUI_BUTTON_OFF] = Graphics()->LoadTexture("images/gui/button_off.png", IStorage::TYPE_ALL);
        m_aGuiTextures[GUI_BUTTON_ON] = Graphics()->LoadTexture("images/gui/button_on.png", IStorage::TYPE_ALL);
        m_aGuiTextures[GUI_ICON_EMOTICON_MUTE] = Graphics()->LoadTexture("images/gui/icon_emoticon_mute.png", IStorage::TYPE_ALL);
        m_aGuiTextures[GUI_ICON_FRIEND] = Graphics()->LoadTexture("images/gui/icon_friend.png", IStorage::TYPE_ALL);
        m_aGuiTextures[GUI_ICON_MUTE] = Graphics()->LoadTexture("images/gui/icon_mute.png", IStorage::TYPE_ALL);
        m_aGuiTextures[GUI_SPEED_ARROW] = Graphics()->LoadTexture("images/gui/speed_arrow.png", IStorage::TYPE_ALL);
    }
    catch(const std::exception& e)
    {
        log_error("gui", "Failed to load gui textures: %s", e.what());
    }
    
}

void CTextures::ReloadHud()
{
    try
    {
        for(auto &HudTexture : m_aHudTextures)
        {
            if(HudTexture.IsValid())
                Graphics()->UnloadTexture(&HudTexture);
        }

        m_aHudTextures[HUD_AIRJUMP_EMPTY] = Graphics()->LoadTexture("images/hud/airjump_empty.png", IStorage::TYPE_ALL);
        m_aHudTextures[HUD_AIRJUMP_FULL] = Graphics()->LoadTexture("images/hud/airjump_full.png", IStorage::TYPE_ALL);
        m_aHudTextures[HUD_ARMOR_EMPTY] = Graphics()->LoadTexture("images/hud/armor_empty.png", IStorage::TYPE_ALL);
        m_aHudTextures[HUD_ARMOR_FULL] = Graphics()->LoadTexture("images/hud/armor_full.png", IStorage::TYPE_ALL);
        m_aHudTextures[HUD_ARROW] = Graphics()->LoadTexture("images/hud/arrow.png", IStorage::TYPE_ALL);
        m_aHudTextures[HUD_HEALTH_EMPTY] = Graphics()->LoadTexture("images/hud/health_empty.png", IStorage::TYPE_ALL);
        m_aHudTextures[HUD_HEALTH_FULL] = Graphics()->LoadTexture("images/hud/health_full.png", IStorage::TYPE_ALL);
        m_aHudTextures[HUD_COLLISION_DISABLED] = Graphics()->LoadTexture("images/hud/collision_disabled.png", IStorage::TYPE_ALL);
        m_aHudTextures[HUD_DEEP_FROZEN] = Graphics()->LoadTexture("images/hud/deep_frozen.png", IStorage::TYPE_ALL);
        m_aHudTextures[HUD_LIVE_FROZEN] = Graphics()->LoadTexture("images/hud/live_frozen.png", IStorage::TYPE_ALL);
        m_aHudTextures[HUD_DUMMY_COPY] = Graphics()->LoadTexture("images/hud/dummy_copy.png", IStorage::TYPE_ALL);
        m_aHudTextures[HUD_DUMMY_HAMMER] = Graphics()->LoadTexture("images/hud/dummy_hammer.png", IStorage::TYPE_ALL);
        m_aHudTextures[HUD_ENDLESS_HOOK] = Graphics()->LoadTexture("images/hud/endless_hook.png", IStorage::TYPE_ALL);
        m_aHudTextures[HUD_ENDLESS_JUMP] = Graphics()->LoadTexture("images/hud/endless_jump.png", IStorage::TYPE_ALL);
        m_aHudTextures[HUD_FREEZE_BAR_EMPTY] = Graphics()->LoadTexture("images/hud/freeze_bar_empty.png", IStorage::TYPE_ALL);
        m_aHudTextures[HUD_FREEZE_BAR_EMPTY_RIGHT] = Graphics()->LoadTexture("images/hud/freeze_bar_empty_right.png", IStorage::TYPE_ALL);
        m_aHudTextures[HUD_FREEZE_BAR_FULL] = Graphics()->LoadTexture("images/hud/freeze_bar_full.png", IStorage::TYPE_ALL);
        m_aHudTextures[HUD_FREEZE_BAR_FULL_LEFT] = Graphics()->LoadTexture("images/hud/freeze_bar_full_left.png", IStorage::TYPE_ALL);
        m_aHudTextures[HUD_GUN_HIT_DISABLED] = Graphics()->LoadTexture("images/hud/gun_hit_disabled.png", IStorage::TYPE_ALL);
        m_aHudTextures[HUD_HOOK_HIT_DISABLED] = Graphics()->LoadTexture("images/hud/hook_hit_disabled.png", IStorage::TYPE_ALL);
        m_aHudTextures[HUD_HAMMER_HIT_DISABLED] = Graphics()->LoadTexture("images/hud/hammer_hit_disabled.png", IStorage::TYPE_ALL);
        m_aHudTextures[HUD_SHOTGUN_HIT_DISABLED] = Graphics()->LoadTexture("images/hud/shotgun_hit_disabled.png", IStorage::TYPE_ALL);
        m_aHudTextures[HUD_GRENADE_HIT_DISABLED] = Graphics()->LoadTexture("images/hud/grenade_hit_disabled.png", IStorage::TYPE_ALL);
        m_aHudTextures[HUD_LASER_HIT_DISABLED] = Graphics()->LoadTexture("images/hud/laser_hit_disabled.png", IStorage::TYPE_ALL);
        m_aHudTextures[HUD_JETPACK] = Graphics()->LoadTexture("images/hud/jetpack.png", IStorage::TYPE_ALL);
        m_aHudTextures[HUD_NINJA_BAR_EMPTY] = Graphics()->LoadTexture("images/hud/ninja_bar_empty.png", IStorage::TYPE_ALL);
        m_aHudTextures[HUD_NINJA_BAR_EMPTY_RIGHT] = Graphics()->LoadTexture("images/hud/ninja_bar_empty_right.png", IStorage::TYPE_ALL);
        m_aHudTextures[HUD_NINJA_BAR_FULL] = Graphics()->LoadTexture("images/hud/ninja_bar_full.png", IStorage::TYPE_ALL);
        m_aHudTextures[HUD_NINJA_BAR_FULL_LEFT] = Graphics()->LoadTexture("images/hud/ninja_bar_full_left.png", IStorage::TYPE_ALL);
        m_aHudTextures[HUD_PRACTICE_MODE] = Graphics()->LoadTexture("images/hud/practice_mode.png", IStorage::TYPE_ALL);
        m_aHudTextures[HUD_SOLO] = Graphics()->LoadTexture("images/hud/solo.png", IStorage::TYPE_ALL);
        m_aHudTextures[HUD_TELEPORT_GRENADE] = Graphics()->LoadTexture("images/hud/teleport_grenade.png", IStorage::TYPE_ALL);
        m_aHudTextures[HUD_TELEPORT_GUN] = Graphics()->LoadTexture("images/hud/teleport_gun.png", IStorage::TYPE_ALL);
        m_aHudTextures[HUD_TELEPORT_LASER] = Graphics()->LoadTexture("images/hud/teleport_laser.png", IStorage::TYPE_ALL);
        m_aHudTextures[HUD_STRONG_HOOK] = Graphics()->LoadTexture("images/hud/strong_hook.png", IStorage::TYPE_ALL);
        m_aHudTextures[HUD_WEAK_HOOK] = Graphics()->LoadTexture("images/hud/weak_hook.png", IStorage::TYPE_ALL);
        m_aHudTextures[HUD_LOCK_MODE] = Graphics()->LoadTexture("images/hud/lock_mode.png", IStorage::TYPE_ALL);
        m_aHudTextures[HUD_TEAM_0_MODE] = Graphics()->LoadTexture("images/hud/team_0_mode.png", IStorage::TYPE_ALL);
        m_aHudTextures[HUD_RACE_FLAG] = Graphics()->LoadTexture("images/hud/race_flag.png", IStorage::TYPE_ALL);
    }
    catch(const std::exception& e)
    {
        log_error("hud", "Failed to load HUD textures: %s", e.what());
    }
    
}

void CTextures::ReloadMapItems()
{
    try
    {
        for(auto &MapItemTexture : m_aMapItemTextures)
        {
            if(MapItemTexture.IsValid())
                Graphics()->UnloadTexture(&MapItemTexture);
        }

        for(auto &MapItemPickupArmor : m_aMapItemPickupArmors)
        {
            if(MapItemPickupArmor.IsValid())
                Graphics()->UnloadTexture(&MapItemPickupArmor);
        }
        
        m_aMapItemTextures[MAPITEM_FLAG_BLUE] = Graphics()->LoadTexture("images/map_items/flag_blue.png", IStorage::TYPE_ALL);
        m_aMapItemTextures[MAPITEM_FLAG_RED] = Graphics()->LoadTexture("images/map_items/flag_red.png", IStorage::TYPE_ALL);
        m_aMapItemTextures[MAPITEM_PICKUP_ARMOR] = Graphics()->LoadTexture("images/map_items/pickup_armor.png", IStorage::TYPE_ALL);
        m_aMapItemTextures[MAPITEM_PICKUP_ARMOR_GRENADE] = Graphics()->LoadTexture("images/map_items/pickup_armor_grenade.png", IStorage::TYPE_ALL);
        m_aMapItemTextures[MAPITEM_PICKUP_ARMOR_LASER] = Graphics()->LoadTexture("images/map_items/pickup_armor_laser.png", IStorage::TYPE_ALL);
        m_aMapItemTextures[MAPITEM_PICKUP_ARMOR_NINJA] = Graphics()->LoadTexture("images/map_items/pickup_armor_ninja.png", IStorage::TYPE_ALL);
        m_aMapItemTextures[MAPITEM_PICKUP_ARMOR_SHOTGUN] = Graphics()->LoadTexture("images/map_items/pickup_armor_shotgun.png", IStorage::TYPE_ALL);
        m_aMapItemTextures[MAPITEM_PICKUP_HEALTH] = Graphics()->LoadTexture("images/map_items/pickup_health.png", IStorage::TYPE_ALL);
        m_aMapItemTextures[MAPITEM_PICKUP_MISC] = Graphics()->LoadTexture("images/map_items/pickup_misc.png", IStorage::TYPE_ALL);

        m_aMapItemPickupArmors[0] = m_aMapItemTextures[MAPITEM_PICKUP_ARMOR_SHOTGUN];
        m_aMapItemPickupArmors[1] = m_aMapItemTextures[MAPITEM_PICKUP_ARMOR_GRENADE];
        m_aMapItemPickupArmors[2] = m_aMapItemTextures[MAPITEM_PICKUP_ARMOR_NINJA];
        m_aMapItemPickupArmors[3] = m_aMapItemTextures[MAPITEM_PICKUP_ARMOR_LASER];
    }
    catch(const std::exception& e)
    {
        log_error("map_items", "Failed to load map item textures: %s", e.what());
    }
    
}

void CTextures::ReloadParticles()
{
    try
    {
        for(auto &ParticleTexture : m_aParticleTextures)
        {
            if(ParticleTexture.IsValid())
                Graphics()->UnloadTexture(&ParticleTexture);
        }

        for(auto &ParticleSplats : m_aParticleSplats)
        {
            if(ParticleSplats.IsValid())
                Graphics()->UnloadTexture(&ParticleSplats);
        }

        m_aParticleTextures[PARTICLE_AIR_JUMP] = Graphics()->LoadTexture("images/particles/air_jump.png", IStorage::TYPE_ALL);
        m_aParticleTextures[PARTICLE_BALL] = Graphics()->LoadTexture("images/particles/ball.png", IStorage::TYPE_ALL);
        m_aParticleTextures[PARTICLE_EXPLOSION_1] = Graphics()->LoadTexture("images/particles/explosion_1.png", IStorage::TYPE_ALL);
        m_aParticleTextures[PARTICLE_HIT_01] = Graphics()->LoadTexture("images/particles/hit_01.png", IStorage::TYPE_ALL);
        m_aParticleTextures[PARTICLE_SHELL] = Graphics()->LoadTexture("images/particles/shell.png", IStorage::TYPE_ALL);
        m_aParticleTextures[PARTICLE_SLICE] = Graphics()->LoadTexture("images/particles/slice.png", IStorage::TYPE_ALL);
        m_aParticleTextures[PARTICLE_SMOKE] = Graphics()->LoadTexture("images/particles/smoke.png", IStorage::TYPE_ALL);
        m_aParticleTextures[PARTICLE_SNOWFLAKE] = Graphics()->LoadTexture("images/particles/snowflake.png", IStorage::TYPE_ALL);
        m_aParticleTextures[PARTICLE_SPLAT_1] = Graphics()->LoadTexture("images/particles/splat_1.png", IStorage::TYPE_ALL);
        m_aParticleTextures[PARTICLE_SPLAT_2] = Graphics()->LoadTexture("images/particles/splat_2.png", IStorage::TYPE_ALL);
        m_aParticleTextures[PARTICLE_SPLAT_3] = Graphics()->LoadTexture("images/particles/splat_3.png", IStorage::TYPE_ALL);
        m_aParticleTextures[PARTICLE_MISC_1] = Graphics()->LoadTexture("images/particles/misc_1.png", IStorage::TYPE_ALL);
        m_aParticleTextures[PARTICLE_MISC_2] = Graphics()->LoadTexture("images/particles/misc_2.png", IStorage::TYPE_ALL);
        m_aParticleTextures[PARTICLE_MISC_3] = Graphics()->LoadTexture("images/particles/misc_3.png", IStorage::TYPE_ALL);
        m_aParticleTextures[PARTICLE_MISC_4] = Graphics()->LoadTexture("images/particles/misc_4.png", IStorage::TYPE_ALL);
        m_aParticleTextures[PARTICLE_MISC_5] = Graphics()->LoadTexture("images/particles/misc_5.png", IStorage::TYPE_ALL);
        m_aParticleTextures[PARTICLE_MISC_6] = Graphics()->LoadTexture("images/particles/misc_6.png", IStorage::TYPE_ALL);
        m_aParticleTextures[PARTICLE_MISC_7] = Graphics()->LoadTexture("images/particles/misc_7.png", IStorage::TYPE_ALL);
        m_aParticleTextures[PARTICLE_MISC_8] = Graphics()->LoadTexture("images/particles/misc_8.png", IStorage::TYPE_ALL);
        m_aParticleTextures[PARTICLE_MISC_9] = Graphics()->LoadTexture("images/particles/misc_9.png", IStorage::TYPE_ALL);
        m_aParticleTextures[PARTICLE_SPARKLE] = Graphics()->LoadTexture("images/particles/sparkle.png", IStorage::TYPE_ALL);
        m_aParticleTextures[PARTICLE_STAR_1] = Graphics()->LoadTexture("images/particles/star_1.png", IStorage::TYPE_ALL);
        m_aParticleTextures[PARTICLE_STAR_2] = Graphics()->LoadTexture("images/particles/star_2.png", IStorage::TYPE_ALL);
        m_aParticleTextures[PARTICLE_STAR_3] = Graphics()->LoadTexture("images/particles/star_3.png", IStorage::TYPE_ALL);

        m_aParticleSplats[0] = m_aParticleTextures[PARTICLE_SPLAT_1];
        m_aParticleSplats[1] = m_aParticleTextures[PARTICLE_SPLAT_2];
        m_aParticleSplats[2] = m_aParticleTextures[PARTICLE_SPLAT_3];
    }
    catch(const std::exception& e)
    {
        log_error("particles", "Failed to load particle textures: %s", e.what());
    }
    
}

void CTextures::ReloadWeapons()
{
    try
    {
        for(auto &WeaponTexture : m_aWeaponTextures)
        {
            if(WeaponTexture.IsValid())
                Graphics()->UnloadTexture(&WeaponTexture);
        }

        for(auto &WeaponBodies : m_aWeaponBodies)
        {
            if(WeaponBodies.IsValid())
                Graphics()->UnloadTexture(&WeaponBodies);
        }

        for(auto &WeaponCursors : m_aWeaponCursors)
        {
            if(WeaponCursors.IsValid())
                Graphics()->UnloadTexture(&WeaponCursors);
        }

        for(auto &WeaponProjectiles : m_aWeaponProjectiles)
        {
            if(WeaponProjectiles.IsValid())
                Graphics()->UnloadTexture(&WeaponProjectiles);
        }

		for(int i = 0; i < 3; ++i)
		{
			Graphics()->UnloadTexture(&m_aWeaponGunMuzzles[i]);
			Graphics()->UnloadTexture(&m_aWeaponShotgunMuzzles[i]);
			Graphics()->UnloadTexture(&m_aWeaponNinjaMuzzles[i]);

			for(auto &WeaponMuzzles : m_aaWeaponMuzzles)
			{
				WeaponMuzzles[i] = IGraphics::CTextureHandle();
			}
		}

        m_aWeaponTextures[WEAPON_HOOK_CHAIN] = Graphics()->LoadTexture("images/weapons/hook_chain.png", IStorage::TYPE_ALL);
        m_aWeaponTextures[WEAPON_HOOK_HEAD] = Graphics()->LoadTexture("images/weapons/hook_head.png", IStorage::TYPE_ALL);
        m_aWeaponTextures[WEAPON_HAMMER_BODY] = Graphics()->LoadTexture("images/weapons/hammer_body.png", IStorage::TYPE_ALL);
        m_aWeaponTextures[WEAPON_HAMMER_CURSOR] = Graphics()->LoadTexture("images/weapons/hammer_cursor.png", IStorage::TYPE_ALL);
        m_aWeaponTextures[WEAPON_GUN_BODY] = Graphics()->LoadTexture("images/weapons/gun_body.png", IStorage::TYPE_ALL);
        m_aWeaponTextures[WEAPON_GUN_CURSOR] = Graphics()->LoadTexture("images/weapons/gun_cursor.png", IStorage::TYPE_ALL);
        m_aWeaponTextures[WEAPON_GUN_PROJ] = Graphics()->LoadTexture("images/weapons/gun_proj.png", IStorage::TYPE_ALL);
        m_aWeaponTextures[WEAPON_GUN_MUZZLE_1] = Graphics()->LoadTexture("images/weapons/gun_muzzle_1.png", IStorage::TYPE_ALL);
        m_aWeaponTextures[WEAPON_GUN_MUZZLE_2] = Graphics()->LoadTexture("images/weapons/gun_muzzle_2.png", IStorage::TYPE_ALL);
        m_aWeaponTextures[WEAPON_GUN_MUZZLE_3] = Graphics()->LoadTexture("images/weapons/gun_muzzle_3.png", IStorage::TYPE_ALL);
        m_aWeaponTextures[WEAPON_SHOTGUN_BODY] = Graphics()->LoadTexture("images/weapons/shotgun_body.png", IStorage::TYPE_ALL);
        m_aWeaponTextures[WEAPON_SHOTGUN_CURSOR] = Graphics()->LoadTexture("images/weapons/shotgun_cursor.png", IStorage::TYPE_ALL);
        m_aWeaponTextures[WEAPON_SHOTGUN_PROJ] = Graphics()->LoadTexture("images/weapons/shotgun_proj.png", IStorage::TYPE_ALL);
        m_aWeaponTextures[WEAPON_SHOTGUN_MUZZLE_1] = Graphics()->LoadTexture("images/weapons/shotgun_muzzle_1.png", IStorage::TYPE_ALL);
        m_aWeaponTextures[WEAPON_SHOTGUN_MUZZLE_2] = Graphics()->LoadTexture("images/weapons/shotgun_muzzle_2.png", IStorage::TYPE_ALL);
        m_aWeaponTextures[WEAPON_SHOTGUN_MUZZLE_3] = Graphics()->LoadTexture("images/weapons/shotgun_muzzle_3.png", IStorage::TYPE_ALL);
        m_aWeaponTextures[WEAPON_GRENADE_BODY] = Graphics()->LoadTexture("images/weapons/grenade_body.png", IStorage::TYPE_ALL);
        m_aWeaponTextures[WEAPON_GRENADE_CURSOR] = Graphics()->LoadTexture("images/weapons/grenade_cursor.png", IStorage::TYPE_ALL);
        m_aWeaponTextures[WEAPON_GRENADE_PROJ] = Graphics()->LoadTexture("images/weapons/grenade_proj.png", IStorage::TYPE_ALL);
        m_aWeaponTextures[WEAPON_LASER_BODY] = Graphics()->LoadTexture("images/weapons/laser_body.png", IStorage::TYPE_ALL);
        m_aWeaponTextures[WEAPON_LASER_CURSOR] = Graphics()->LoadTexture("images/weapons/laser_cursor.png", IStorage::TYPE_ALL);
        m_aWeaponTextures[WEAPON_LASER_PROJ] = Graphics()->LoadTexture("images/weapons/laser_proj.png", IStorage::TYPE_ALL);
        m_aWeaponTextures[WEAPON_NINJA_BODY] = Graphics()->LoadTexture("images/weapons/ninja_body.png", IStorage::TYPE_ALL);
        m_aWeaponTextures[WEAPON_NINJA_CURSOR] = Graphics()->LoadTexture("images/weapons/ninja_cursor.png", IStorage::TYPE_ALL);
        m_aWeaponTextures[WEAPON_NINJA_MUZZLE_1] = Graphics()->LoadTexture("images/weapons/ninja_muzzle_1.png", IStorage::TYPE_ALL);
        m_aWeaponTextures[WEAPON_NINJA_MUZZLE_2] = Graphics()->LoadTexture("images/weapons/ninja_muzzle_2.png", IStorage::TYPE_ALL);
        m_aWeaponTextures[WEAPON_NINJA_MUZZLE_3] = Graphics()->LoadTexture("images/weapons/ninja_muzzle_3.png", IStorage::TYPE_ALL);

        m_aWeaponBodies[0] = m_aWeaponTextures[WEAPON_HAMMER_BODY];
        m_aWeaponBodies[1] = m_aWeaponTextures[WEAPON_GUN_BODY];
        m_aWeaponBodies[2] = m_aWeaponTextures[WEAPON_SHOTGUN_BODY];
        m_aWeaponBodies[3] = m_aWeaponTextures[WEAPON_GRENADE_BODY];
        m_aWeaponBodies[4] = m_aWeaponTextures[WEAPON_LASER_BODY];
        m_aWeaponBodies[5] = m_aWeaponTextures[WEAPON_NINJA_BODY];

        m_aWeaponCursors[0] = m_aWeaponTextures[WEAPON_HAMMER_CURSOR];
        m_aWeaponCursors[1] = m_aWeaponTextures[WEAPON_GUN_CURSOR];
        m_aWeaponCursors[2] = m_aWeaponTextures[WEAPON_SHOTGUN_CURSOR];
        m_aWeaponCursors[3] = m_aWeaponTextures[WEAPON_GRENADE_CURSOR];
        m_aWeaponCursors[4] = m_aWeaponTextures[WEAPON_LASER_CURSOR];
        m_aWeaponCursors[5] = m_aWeaponTextures[WEAPON_NINJA_CURSOR];

        m_aWeaponProjectiles[0] = m_aWeaponTextures[WEAPON_HAMMER_BODY];
        m_aWeaponProjectiles[1] = m_aWeaponTextures[WEAPON_GUN_PROJ];
        m_aWeaponProjectiles[2] = m_aWeaponTextures[WEAPON_SHOTGUN_PROJ];
        m_aWeaponProjectiles[3] = m_aWeaponTextures[WEAPON_GRENADE_PROJ];
        m_aWeaponProjectiles[4] = m_aWeaponTextures[WEAPON_LASER_PROJ];
        m_aWeaponProjectiles[5] = m_aWeaponTextures[WEAPON_NINJA_BODY];

        // muzzles
		for(int i = 0; i < 3; ++i)
		{
            m_aWeaponGunMuzzles[i] = m_aWeaponTextures[WEAPON_GUN_MUZZLE_1 + i];
            m_aWeaponShotgunMuzzles[i] = m_aWeaponTextures[WEAPON_SHOTGUN_MUZZLE_1 + i];
            m_aWeaponNinjaMuzzles[i] = m_aWeaponTextures[WEAPON_NINJA_MUZZLE_1 + i];

			m_aaWeaponMuzzles[1][i] = m_aWeaponGunMuzzles[i];
			m_aaWeaponMuzzles[2][i] = m_aWeaponShotgunMuzzles[i];
			m_aaWeaponMuzzles[5][i] = m_aWeaponNinjaMuzzles[i];
		}
    }
    catch(const std::exception& e)
    {
        log_error("weapons", "Failed to load weapon textures: %s", e.what());
    }
    
}

IGraphics::CTextureHandle CTextures::EmoticonTexture(int Index) 
{
	return m_aEmoticonTextures[Index];
}

IGraphics::CTextureHandle CTextures::GuiTexture(int Index) 
{
	return m_aGuiTextures[Index];
}

IGraphics::CTextureHandle CTextures::HudTexture(int Index) 
{
	return m_aHudTextures[Index];
}

IGraphics::CTextureHandle CTextures::MapItemTexture(int Index) 
{
	return m_aMapItemTextures[Index];
}

IGraphics::CTextureHandle CTextures::ParticleTexture(int Index) 
{
	return m_aParticleTextures[Index];
}

IGraphics::CTextureHandle CTextures::WeaponTexture(int Index) 
{
	return m_aWeaponTextures[Index];
}