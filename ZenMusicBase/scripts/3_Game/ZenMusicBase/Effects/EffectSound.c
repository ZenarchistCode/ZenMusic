modded class EffectSound
{
	#ifndef ZenModPack
	void Zen_SetMaxVolume(float v)
	{
		m_SoundWaveVolumeMax = v;
	}

	AbstractWave Zen_GetAbstractWave()
	{
		return m_SoundWaveObject;
	}
	#endif
}