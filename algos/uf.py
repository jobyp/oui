#!/usr/bin/env python

# Dynamic Connectivity 
# --------------------

# The input is a sequence of pairs of integers, where
# each integer represents an object of some type and we are to 
# interpret pair p q as "p is connected to q". We assume that
# "is connected to" is an equivalence relation, which means

# -> Reflexive: p ~ p
# -> Symmetric: p ~ q -> q ~ p
# -> Transitive: p ~ q /\ q ~ r -> p ~ r

# An equivalence relation partition objects into equivalence 
# classes.

# Our goal is to write a program to filter out extraneous pairs
# (pairs where both objects are in same equivalence class).


import sys
import fileinput

class UF(object):

    def __init__(self, N):

        # Reflexivity p ~ p
        self.conn = [i for i in range(N + 1)]
        self.components = N
        return
        
    def union(self, p, q):
        p_root = self.find(p)
        q_root = self.find(q)

        if p_root == q_root:
            return

        def reset_root(i):
            if i == q_root:
                return p_root
            else:
                return i

        self.conn = [reset_root(i) for i in self.conn]
        self.components -= 1
        
        return

    def find(self, p):
        assert p < len(self.conn)
        return self.conn[p]
        
    def connected(self, p, q):
        return self.find(p) == self.find(q)
        
    def count():
        return self.components

class QuickUnion_UF(UF):
    
    def __init__(self, N):
        super(QuickUnion_UF, self).__init__(N)
        self.weights = [1 for i in self.conn]

    def union(self, p, q):
        p_root = self.find(p)
        q_root = self.find(q)

        if p_root == q_root:
            return
    
        if self.weights[q_root] < self.weights[p_root]:
            self.conn[q_root] = p_root
            self.weights[p_root] += self.weights[q_root]
        else:
            self.conn[p_root] = q_root
            self.weights[q_root] += self.weights[p_root]

        self.components -= 1
        return

    def find(self, p):

        assert p < len(self.conn)

        while p != self.conn[p]:
            p = self.conn[p]
            
        return p
        
    
if __name__ == "__main__":
    
    pairs = fileinput.input()
    N = int(next(pairs, 0))
    uf = UF(N)
    
    for l in pairs:
        p, q = tuple(map(int, l.split()))
        if not uf.connected(p, q):
            uf.union(p, q)
            #print "%d   %d" % (p, q)

    print "Components == %d" % uf.count()

    sys.exit(0)
