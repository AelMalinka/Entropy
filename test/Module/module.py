print("PyModule::load()")

class Module:
    def __init__(self):
        print("PyModule::__init__()")
    def __getitem__(self, index):
        print("PyModule::operator[]:", index)
    def run(self):
        print("PyModule::run()")
