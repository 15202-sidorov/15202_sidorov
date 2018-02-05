from ui.AlgorithmLabel import AlgorithmLabel

class VIOLAAlgorithmLabel( AlgorithmLabel ):
    def __init__(self, string):
        AlgorithmLabel.__init__(self, string)
        self.algNo = 1