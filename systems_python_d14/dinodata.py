import re
from base64 import b64encode, b64decode
from simplecrypt import encrypt, decrypt

class dinodata:
    def __init__(self, encryptpw):
        self.dinoframe = ""
        self.errors = 0
        self.encryptpw = encryptpw
    
    def readdinos(self, datfile):
        f = open(datfile)
        self.headers = f.readline().split('\t')
        errors = 0
        dinoframe = list()
        for line in f:
            splitline = line.split('\t')
            if(len(splitline) == len(self.headers)):
                dinoframe.append(splitline)
            else:
                errors += 1
        self.dinoframe = dinoframe
        self.errors = errors
        f.close()
        return 

    def preypredrat(self, preys, preds):
        num_prey = 0
        num_pred = 0
        for prey in preys:
            for line in self.dinoframe:
                name = line[5]
                # check if the line is one of the prey
                if re.search('.*'+ re.escape(prey) + '.*', name, re.IGNORECASE):
                    num_prey += 1
        for pred in preds:
            for line in self.dinoframe:
                name = line[5]
                # check if the line is one of the prey
                if re.search('.*'+ re.escape(pred) + '.*', name, re.IGNORECASE):
                    num_pred += 1

        return num_prey, num_pred, num_prey/num_pred

    def dinoencrypt(fcn):
        def inner(self, datfile, dat):
            edat = dat
            if(self.encryptpw): # if we have a key we encrypt
                edat = encrypt(self.encryptpw, dat)
                edat = b64encode(edat).decode('utf-8')
            # call function in all cases
            fcn(self, datfile, edat)
        return inner

    # wrapper func:

    # def manager(fcn):
    #   def inner(parameter a, b ,c):
    #       do stuff
    #       fcn(a,b,c)
    #   return inner
            

    @dinoencrypt
    def filewriteline(self, datfile, dat):
        fd = open(datfile, 'a')
        fd.write(dat)
        fd.write('\n')
        fd.close()
    #same as doing filewriteline = dinoencrypt(filewriteline)

    def save_df(self, datfile_out, columns, limit):
        dat = ""
        k = 0
        for j in columns:
            if k < len(columns) - 1:
                dat += self.headers[j] + '\t'
            else:
                dat += self.headers[j]
            k += 1
        dat += '\n'
        
        for i in range(limit):
            k = 0
            for j in columns:
                if k < len(columns) - 1:
                    dat += self.dinoframe[i][j] + '\t'
                else:
                    dat += self.dinoframe[i][j]
                k += 1
            if i < limit - 1:
                dat += '\n'
        self.filewriteline(datfile_out, dat)