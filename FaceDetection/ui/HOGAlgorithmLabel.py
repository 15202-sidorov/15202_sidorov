from ui.AlgorithmLabel import AlgorithmLabel

class HOGAlgorithmLabel( AlgorithmLabel ):
    def __init__(self, string):
        AlgorithmLabel.__init__(self, string)
        self.algNo = 0