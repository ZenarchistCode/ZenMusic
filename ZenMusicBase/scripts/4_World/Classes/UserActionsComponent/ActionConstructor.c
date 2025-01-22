modded class ActionConstructor
{
    override void RegisterActions(TTypenameArray actions)
    {
        super.RegisterActions(actions);

        actions.Insert(ActionToggleMusic);
        actions.Insert(ActionMusicVolUp);
        actions.Insert(ActionMusicVolDn);
        actions.Insert(ActionBoomboxVolUp);
        actions.Insert(ActionBoomboxVolDown);
        actions.Insert(ActionStaticBoomboxTurnOn);
        actions.Insert(ActionStaticBoomboxTurnOff);
        actions.Insert(ActionStaticBoomboxNextSong);
    }
}