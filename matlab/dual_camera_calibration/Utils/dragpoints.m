function dragpoints(ax,currCentroid)

%can change the marker size or marker type to make it more visible.
%Currently is set to small points at a size of 2 so is not very visible.
plot(ax,currCentroid(1),currCentroid(2),'rx','LineWidth',2,'hittest','on','buttondownfcn',@clickmarker);
ax.XLim = currCentroid(1)+[-50 50];
ax.YLim = currCentroid(2)+[-50 50];

function clickmarker(src,ev)
set(ancestor(src,'figure'),'windowbuttonmotionfcn',{@dragmarker,src})
set(ancestor(src,'figure'),'windowbuttonupfcn',@stopdragging)

function dragmarker(fig,ev,src)

%get current axes and coords
h1 = evalin('base','ax');
coords=get(h1,'currentpoint');

%create new x and y data and exchange coords for the dragged point
x_new=coords(1,1);
y_new=coords(1,2);

%update plot
set(src,'xdata',x_new,'ydata',y_new);
assignin('base','currCentroid',coords(1,1:2));

function stopdragging(fig,ev)
set(fig,'windowbuttonmotionfcn','')
set(fig,'windowbuttonupfcn','')