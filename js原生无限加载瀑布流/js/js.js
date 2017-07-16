function waterfall(parent,box){
   // 将parent中box获取
   var oparent=document.getElementById(parent);
   var oboxs=getByClass(oparent,box);
   //计算列数  页面宽/box的宽
   var oBoxW=oboxs[0].offsetWidth;//获取box宽
   var cols=Math.floor(document.documentElement.clientWidth/oBoxW);//获取页面宽度
   //设置main的宽
   oparent.style.cssText='width:'+oBoxW*cols+'px;margin:0 auto';
   //设置图片位置(找最矮)
   var hArr=new Array();
   for(var i=0;i<oboxs.length;i++){
   	if(i<cols){
   		hArr.push(oboxs[i].offsetHeight);//获取第一行cols个盒子高
   	}else //找最小
   	{
   		var minH=Math.min.apply(null,hArr);//找最小
   		var index=getMinhindex(hArr,minH);//找下标
   		oboxs[i].style.position='absolute';
   		oboxs[i].style.top=minH+'px';   //设置下一个的位置
   		oboxs[i].style.left=oBoxW*index+'px';
   		//改变数组，对应列高
   		hArr[index]+=oboxs[i].offsetHeight;
   	}
   }
}
//根据class获取指定id中的box
function getByClass(parent,classname)
{
	var boxArr=new Array();//保存所有box元素
	oElement=parent.getElementsByTagName('*');//先获取所有元素
	for(var i=0;i<oElement.length;i++){
		if(oElement[i].className==classname){
			boxArr.push(oElement[i]);
		}
	}
	return boxArr;
}
function getMinhindex(arr,val){
	for(i=0;i<arr.length;i++)
	{
		if(arr[i]==val)
		{
			return i;
		}
	}
}
//检测是否加载
function checkSlide(){
	var oParent=document.getElementById('main');
	var oBoxs=getByClass(oParent,'box');  //获取最后一个
	var lastBoxH=oBoxs[oBoxs.length-1].offsetTop+Math.floor(oBoxs[oBoxs.length-1].offsetHeight/2);  //最后一个一半的高度
	var scrollTop=document.body.scrollTop||document.documentElement.scrollTop;     //页面高度
	var height=document.body.clientHeight||document.documentElement.clientHeight; //可视大小
	return (lastBoxH<scrollTop+height)?true:false;
}
function checkHeght(){
	var oParent=document.getElementById('main');
	var oBoxs=getByClass(oParent,'box');  //获取最后一个
	var lastBoxB=oBoxs[oBoxs.length-1].offsetTop//最后一个的高度
	var height=document.body.clientHeight||document.documentElement.clientHeight; //可视大小
	return (lastBoxB<height)?true:false;
}
waterfall('main','box');
var dataInt={"data":[{"src":'0.jpg'},{"src":'1.jpg'},{"src":'2.jpg'},{"src":'3.jpg'},{"src":'4.jpg'},{"src":'5.jpg'},{"src":'6.jpg'},{"src":'7.jpg'},{"src":'8.jpg'},{"src":'9.jpg'},{"src":'10.jpg'}]}; //模拟数据
//填充
function full(){
	var oParent=document.getElementById('main');
	if(checkHeght)
	{
		for(var i=0;i<dataInt.data.length;i++){
			var oBox=document.createElement('div');
			oBox.className='box';
			oParent.appendChild(oBox);//将box放入main
			var oPic=document.createElement('div');
			oPic.className='pic';
			oBox.appendChild(oPic);//将pic放入box;
			var oImg=document.createElement('img');
		    oImg.src="img/"+dataInt.data[i].src;    //添加图片到Pic
		    oPic.appendChild(oImg);
		}
		waterfall('main','box');
	}else
	{
		return;
	}
}
//拖动触发加载  初始高度一定高于本页面
//或者是最后一张图片高度小于可视大小
full();
window.onscroll=function(){
	var oParent=document.getElementById('main');
	if(checkSlide){  //开始加载 (json)
		//将数据 加入页面
		for(var i=0;i<dataInt.data.length;i++){
			var oBox=document.createElement('div');
			oBox.className='box';
			oParent.appendChild(oBox);//将box放入main
			var oPic=document.createElement('div');
			oPic.className='pic';
			oBox.appendChild(oPic);//将pic放入box;
			var oImg=document.createElement('img');
		    oImg.src="img/"+dataInt.data[i].src;    //添加图片到Pic
		    oPic.appendChild(oImg);
		}
		waterfall('main','box');
	}
}
