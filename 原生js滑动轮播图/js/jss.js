window.onload = function() {
	var box = document.getElementById('box'); //主框
	var main = document.getElementById('box_main'); //图片集
	var buttons = document.getElementById('selete').getElementsByTagName('li'); //按钮
	var prev = document.getElementById('con_l'); //上箭头
	var next = document.getElementById('con_r'); //下箭头
	var index = 1; //初始显示图片
	var animating = false; //记录动画效果
	var timer = null; //记录timer
	function showButton() {
		for(var i = 0; i < buttons.length; i++) {
			buttons[i].className = ' ' ;
		}
		buttons[index - 1].className = 'on';
	}
	//获取元素
	function animate(offset) {
		animating = true; //防止多崩
		var newLeft = parseInt(main.style.left) + offset;
		var time = 300; //运动总时间
		var interval = 10; //运动间隔
		var speed = offset / (time / interval); //位移距离（算）距离/次数
		function go() { //判断是否运动
			if((speed < 0 && parseInt(main.style.left) > newLeft) || (speed > 0 && parseInt(main.style.left) < newLeft)) {
				main.style.left = parseInt(main.style.left) + speed + 'px';
				setTimeout(arguments.callee, interval);
			} else {
				main.style.left = newLeft + 'px';
				if(newLeft > -450) {
					main.style.left = -2250 + 'px';
				}
				if(newLeft < -2250) {
					main.style.left = -450 + 'px';
				}
				animating = false;
			} //运动完成
		} //判断是否运动
		go();
	}
	//运动函数 重点..
	//自动切换
	function play() {
		timer = setInterval(function() {
			next.onclick();
		}, 2500);
	}

	play();
	box.onmouseover = function() {
		clearInterval(timer);
	}
	box.onmouseout = function() {
		play();
	}
	next.onclick = function() {
		if(animating == false) {
			animate(-450);
			if(index == 5) {
				index = 1;
			} else {
				index += 1;
			}
			showButton()
		}

	}
	prev.onclick = function() {
		if(animating == false) {
			animate(450);
			if(index == 1) {
				index = 5;
			} else {
				index -= 1;
			}
			showButton()
		}

	} //给箭头绑定事件
	//按钮切换
	for(var i = 0; i < buttons.length; i++) {
		buttons[i].onclick = (function(num) {
			return function() {
				var myindex = num + 1;
				var offest = -450 * (myindex - index);
				if(animating == false) {
					animate(offest);
					index = myindex;
					showButton();
				}
			};
		})(i); //闭包绑定事件
	}
}