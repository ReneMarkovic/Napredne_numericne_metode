import numpy as np
import time

def init_S(Nx,Ny):
    return np.zeros([Nx,Ny],int)

def init_F(Nx,Ny,pos,st_zrn):
    F=np.zeros([Nx,Ny],int)
    #pos -> je seznam koordinat
    F[pos[0],pos[1]]=st_zrn
    return F

def TBW_mode(i,j,S,Sth,Nx,Ny):
    global size
    ip=i+1
    im=i-1
    jp=j+1
    jm=j-1
    if S[i,j]>Sth:#Več od štiri #Plaz!!!!!!
        size+=1
        S[i,j]-=4
        if ip%(Nx-1)!=0:
            S[ip,j]+=1
            TBW_mode(ip,j,S,Sth,Nx,Ny)
            
        if im%(Nx)!=0:
            S[im,j]+=1
            TBW_mode(im,j,S,Sth,Nx,Ny)
            
        if jp%(Ny-1)!=0:
            S[i,jp]+=1
            TBW_mode(i,jp,S,Sth,Nx,Ny)
            
        if jm%Ny!=0:
            S[i,jm]+=1
            TBW_mode(i,jm,S,Sth,Nx,Ny)
    return S

def run_model(Nx,Ny,pos,st_zrn,TFIN,Sth):
    #global Sth
    global size
    S=init_S(Nx,Ny)
    F=init_F(Nx,Ny,pos,st_zrn)
    start=time.time()
    lag=100 ##
    dt=[]
    plazovi=[]
    for iteracija in range(TFIN):
        if iteracija%lag==0:
            end=time.time()
            frac=np.sum(S>0)/((Nx-1.0)*(Ny-1.0))
            print('Izračun je %d-tih iteracij je v trajal %.2f s, frame = %d S = %.3f'%(lag,end-start,iteracija,frac),end="\r\n")
            dt.append(end-start)
            start=time.time()
        S=S+F
        size=0
        S=TBW_mode(pos[0],pos[1],S,Sth,Nx,Ny)
        if size>0:
            plazovi.append(size)
    return [plazovi,dt,S]