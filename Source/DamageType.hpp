#pragma once

namespace Damage
{
    enum class Type
    {
        //
        // Summary:
        //     Unknown damage source.
        Unknown,
        //
        // Summary:
        //     Fall damage.
        Falldown,
        //
        // Summary:
        //     Alpha Warhead.
        Warhead,
        //
        // Summary:
        //     LCZ Decontamination.
        Decontamination,
        //
        // Summary:
        //     Exiled.API.Enums.EffectType.Asphyxiated.
        Asphyxiation,
        //
        // Summary:
        //     Exiled.API.Enums.EffectType.Poisoned.
        Poison,
        //
        // Summary:
        //     Exiled.API.Enums.EffectType.Bleeding.
        Bleeding,
        //
        // Summary:
        //     Damage dealt by a Exiled.API.Features.Items.Firearm when the ItemType used is
        //     not available.
        Firearm,
        //
        // Summary:
        //     Damage dealt by a Exiled.API.Features.Items.MicroHid.
        MicroHid,
        //
        // Summary:
        //     Damage dealt by a Tesla Gate.
        Tesla,
        //
        // Summary:
        //     Damage is dealt by a Exiled.API.Enums.Side.Scp when the PlayerRoles.RoleTypeId
        //     used is not available.
        Scp,
        //
        // Summary:
        //     Damage dealt by frag grenades.
        Explosion,
        //
        // Summary:
        //     Damage dealt by SCP-018.
        Scp018,
        //
        // Summary:
        //     Exiled.API.Enums.EffectType.Scp207.
        Scp207,
        //
        // Summary:
        //     Damage is dealt by SCP Recontainment procedure.
        Recontainment,
        //
        // Summary:
        //     Crushed by the checkpoint killer trigger.
        Crushed,
        //
        // Summary:
        //     Damage caused by the femur breaker.
        FemurBreaker,
        //
        // Summary:
        //     Damage caused by the pocket dimension.
        PocketDimension,
        //
        // Summary:
        //     Damage caused by the friendly fire detector.
        FriendlyFireDetector,
        //
        // Summary:
        //     Damage caused by severed hands.
        SeveredHands,
        //
        // Summary:
        //     Damage caused by severed eyes.
        SeveredEyes,
        //
        // Summary:
        //     Damage caused by a custom source.
        Custom,
        //
        // Summary:
        //     Damage caused by PlayerRoles.RoleTypeId.Scp049.
        Scp049,
        //
        // Summary:
        //     Damage caused by PlayerRoles.RoleTypeId.Scp096.
        Scp096,
        //
        // Summary:
        //     Damage caused by PlayerRoles.RoleTypeId.Scp173.
        Scp173,
        //
        // Summary:
        //     Damage caused by PlayerRoles.RoleTypeId.Scp939.
        Scp939,
        //
        // Summary:
        //     Damage caused by PlayerRoles.RoleTypeId.Scp0492.
        Scp0492,
        //
        // Summary:
        //     Damage caused by PlayerRoles.RoleTypeId.Scp106.
        Scp106,
        //
        // Summary:
        //     Damage caused by ItemType.GunCrossvec.
        Crossvec,
        //
        // Summary:
        //     Damage caused by ItemType.GunLogicer.
        Logicer,
        //
        // Summary:
        //     Damage caused by ItemType.GunRevolver.
        Revolver,
        //
        // Summary:
        //     Damage caused by ItemType.GunShotgun.
        Shotgun,
        //
        // Summary:
        //     Damage caused by ItemType.GunAK.
        AK,
        //
        // Summary:
        //     Damage caused by ItemType.GunCOM15.
        Com15,
        //
        // Summary:
        //     Damage caused by ItemType.GunCOM18.
        Com18,
        //
        // Summary:
        //     Damage caused by ItemType.GunFSP9.
        Fsp9,
        //
        // Summary:
        //     Damage caused by ItemType.GunE11SR.
        E11Sr,
        //
        // Summary:
        //     Exiled.API.Enums.EffectType.Hypothermia.
        Hypothermia,
        //
        // Summary:
        //     Damage caused by ItemType.ParticleDisruptor.
        ParticleDisruptor,
        //
        // Summary:
        //     Damage caused by Exiled.API.Enums.EffectType.CardiacArrest.
        CardiacArrest,
        //
        // Summary:
        //     Damage caused by ItemType.GunCom45.
        Com45,
        //
        // Summary:
        //     Damage caused by ItemType.Jailbird.
        Jailbird,
        //
        // Summary:
        //     Damage caused by ItemType.GunFRMG0.
        Frmg0,
        //
        // Summary:
        //     Damage caused by ItemType.GunA7.
        A7,
        //
        // Summary:
        //     Damage caused by PlayerRoles.RoleTypeId.Scp3114
        Scp3114,
        //
        // Summary:
        //     Damage caused by Scp3114's strangling ability.
        Strangled,
        //
        // Summary:
        //     Damage caused by the marshmallow man.
        Marshmallow,
        //
        // Summary:
        //     Damage caused by PlayerRoles.RoleTypeId.Flamingo ,PlayerRoles.RoleTypeId.AlphaFlamingo
        //     or PlayerRoles.RoleTypeId.ZombieFlamingo.
        Scp1507,
        //
        // Summary:
        //     Damage caused by Scp956 the pinata.
        Scp956,
        //
        // Summary:
        //     Damage caused by ItemType.Snowball.
        SnowBall,
        //
        // Summary:
        //     Damage caused by ItemType.GunSCP127.
        Scp127,
        //
        // Summary:
        //     Damage type for PlayerStatsSystem.SilentDamageHandler.
        Silent,
        //
        // Summary:
        //     Damage type for PlayerStatsSystem.GrayCandyDamageHandler.
        GrayCandy,
        //
        // Summary:
        //     Damage caused by ItemType.SCP1509.
        Scp1509
    };
}