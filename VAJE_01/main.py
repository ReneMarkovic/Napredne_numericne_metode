from logging import StreamHandler

from numpy import vectorize
from nnm_package import model,vizualizacija
from IPython.display import clear_output

global Sth,size, TFIN,cx,cy



size=0 #Spremenljivka, ki beleži čez koliko celic se je plaz razširil.
Nx=51 #Število razdelkov na x osi
Ny=51 #Število razdelkov na y osi
TFIN=5000 #Število iteracij
Sth=4 #Mejna vrednost strmine, ki sproži plaz
cx=int(Nx/2) #x lega kjer se spuiščajo zrna peska
cy=int(Ny/2) #y lega kjer se spuiščajo zrna peska
pos=[cx,cy] #seznam leg, kjer se spuščajo zrna peska
st_zrn=4 #ŠTevilo zrn, ki se na vsako lokacijo spussti v vsaki iteraciji
START=int(0.8*TFIN) #Število iteracij, ki se zanemarijo

plazovi,dt,S=model.run_model(Nx,Ny,pos,st_zrn,TFIN,Sth)

save_figure=True
vizualizacija.Fig_1(plazovi,S,Sth,START,save_figure)
vizualizacija.Fig_2(dt,plazovi,START,save_figure)
vizualizacija.Fig_3(plazovi,START,save_figure)
