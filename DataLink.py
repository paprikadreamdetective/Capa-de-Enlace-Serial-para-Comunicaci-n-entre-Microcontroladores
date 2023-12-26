class DataLink:
    class PDU:
        def __init__(self, message):
            self._message = message  

        def message(self):
            return (self._message)

    def encapsulate(self, message):
        pdu = self.PDU(message)
        return (pdu)

    def decapsulate(self, message):
        pdu = self.PDU(message)
        return (pdu)