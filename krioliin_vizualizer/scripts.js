$(document).ready(function()
{
	var		map;
	var		start_pos;
	var		map_x;
	var		map_y;
	var		RUN_GAME;

	$("#button").click(function(){
		map = $('#map_src').val();
	});

	function init_map_size()
	{
		var		size_pos;
	
		size_pos = map.indexOf("Plateau ");
		map_y = map.charAt(size_pos + "Plateau ".length);
		map_y += map.charAt(size_pos + "Plateau ".length + 1);
	
		map_y = map.charAt(size_pos + "Plateau ".length);
		map_y += map.charAt(size_pos + "Plateau ".length + 1);
	
		map_x = map.charAt(size_pos + "Plateau ".length + 3);
		map_x += map.charAt(size_pos + "Plateau ".length + 4);

		$("p").append(" X " + map_x + " Y " + map_y);
	}

	function set_speed()
	{
		var		speed;
	
		speed = $("input[name=choose_speed]:checked", "#map_src_form").val();
		if (String(speed) == "speed_slow")
		{
			$('p').append("1:" + speed);
			return (900);
		}
		if (String(speed) == "speed_fast")
		{
			$('p').append("2:" + speed);
			return (100);
		}
		if (String(speed) == "speed_super_fast")
		{
			$('p').append("3:" + speed);
			return (30);
		}
		return (300);
	}

	function creat_grid_from_div()
	{
		var		i;
	
		i = 0;
		while (i < map_x * map_y)
		{
			$("#grid").append("<div class='spot_div'></div>")
			i++;
		}
	}

	function add_move_player_y(x, y)
	{
		var		spot;
		var		spot_pos;
	
		spot = "#grid div:nth-child(";
		if (0 < y)
		{
			spot_pos = x + (y * map_x);
			$(spot + spot_pos + ')').addClass("player_one");
		}
		else
			$(spot + x + ')').addClass("player_one");
	}

	function add_move_player_o(x, y, character)
	{
		var		spot_pos;
		var		spot;
		var		class_name;

		spot = "#grid div:nth-child(";
		//if (character == 'O')
			class_name = "player_o";
		// else
		// 	class_name = "new_figure_o";
		if (0 < y)
		{
			spot_pos = x + (y * map_x);
			$(spot + spot_pos  + ')').addClass(class_name);
		}
		else
			$(spot + x + ')').addClass(class_name);
	}

	function add_move(map_arr)
	{
		var		x;
		var		y;
	
		x = 0;
		y = 0;
		while (y < map_y)
		{
			while (x < map_x)
			{
				if (map_arr[y][x] == "O")
					add_move_player_o(x, y, map_arr[y][x]);
				if (map_arr[y][x] == "X")
					add_move_player_y(x, y);
				x++;
			}
			x = 0;
			y++;
		}
	}

	function move_start_pos()
	{
		start_pos = map.indexOf("000", Number(start_pos));
		$("p").append("start_pos" + start_pos + "<br>");
		if (Number(start_pos) == -1)
		{
			$("p").append("Minus found" + start_pos + "<br>");
			Number(RUN_GAME) = -1;
			
		}
	}

	function fill_one_map_piece(map_arr)
	{
		var		start;
		var		i;

		i = 0;
		start = Number(start_pos) + 3;
		//$("#paragraph").append("<br>" + "START POSITION 2: " + start_pos);
		while (i < Number(map_y))
		{
		//	$("#paragraph").append("start: " + start + " i: " + i + "<br>");
			map_arr[i] = map.substring(start, Number(start) + Number(map_x));
			start += Number(map_x) + 5;
			i++;
		}
		//setTimeout(add_move, 900*i, map_arr);
		start_pos = start;
	}

	$("#button").click(function()
	{
		var		map_arr = [];
		var		speed;
		var		i;

		i = 0;
		RUN_GAME = 1;
		init_map_size();
		creat_grid_from_div();
		speed = set_speed();
		start_pos = map.indexOf("000");
		while (Number(RUN_GAME) != -1)
		{
			setTimeout(fill_one_map_piece, Number(speed) * i, map_arr);
			setTimeout(add_move, Number(speed) * i, map_arr);
			setTimeout(move_start_pos, Number(speed) * i);
			if (Number(RUN_GAME) == -1)
			{
				$("p").append(" The game is over!");
				break ;
			}
			i++;
		}
	});

	init_map_size();
});
