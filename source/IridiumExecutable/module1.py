from IridiumPython import GameObject

class PyScriptComponent():
    def Start(gameObject):
        gameObject.Name = "Python"
        comp = gameObject.AddMusicComponent()

        comp.AddMusicClip("bgMusic", "../../assets/splash_scene/splashSceneBgMusic.wav")

        comp.PlayMusic("bgMusic")

    def Update(gameObject):
        print("Update")

    def Shutdown(gameObject):
        print("Shutdown")
