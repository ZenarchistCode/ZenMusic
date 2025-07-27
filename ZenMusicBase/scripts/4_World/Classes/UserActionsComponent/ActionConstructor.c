modded class ActionConstructor
{
    override void RegisterActions(TTypenameArray actions)
    {
        super.RegisterActions(actions);

        actions.Insert(ActionZenToggleMusic);
        actions.Insert(ActionZenMusicVolUp);
        actions.Insert(ActionZenMusicVolDn);
        actions.Insert(ActionZenBoomboxVolUp);
        actions.Insert(ActionZenBoomboxVolDown);
        actions.Insert(ActionZenStaticBoomboxTurnOn);
        actions.Insert(ActionZenStaticBoomboxTurnOff);
        actions.Insert(ActionZenStaticBoomboxNextSong);
    }
}