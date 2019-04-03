from IridiumPython import GameObject

class PyScriptComponent():
    def Start(gameObject : GameObject):
        gameObject.Name = "Python"
        print(gameObject.GetComponentMusic())

    def Update(gameObject):
        print("Update")

    def Shutdown(gameObject):
        print("Shutdown")
