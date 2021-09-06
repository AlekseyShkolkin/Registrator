from kivy.app import App
from kivy.uix.label import Label
from kivy.uix.textinput import TextInput
from kivy.uix.boxlayout import BoxLayout
from kivy.core.window import Window
from kivy.uix.button import Button
import pandas as pd

# Глобальные настройки
Window.clearcolor = (255, 255, 255, 1)
Object = '0'
Start = 0.0
Step = 0.0
Km = 0.0
Potencial = 0.0
File=0


def on_focus(instance, value):
    pass

class MyApp(App):
    title = "Регистратор"
    # Создание всех виджетов (объектов)
    def __init__(self):
        super().__init__()
        self.icon = "data/logo/logo3-min.png"
        self.btnBT = Button(text='Подключитесь к устройству',
                            size_hint=(1, None), height=40, font_size = 22,
                            pos_hint={'center_x': .5, 'center_y': .5},
                            color=(0, 47.5, 76.1, 1),
                            background_color=(255,255,255,1))

        self.input_object = TextInput(hint_text='Введите название объекта',
                                      size_hint=(1, None), height=40,font_size = 22,
                                      pos_hint={'center_x': .5, 'center_y': .5},
                                      multiline=False)

        self.input_start = TextInput(hint_text='Начало измерений',
                                      multiline=False,font_size = 22,
                                      pos_hint={'center_x': 0.5, 'center_y': .5},
                                      size_hint=(1, None), height=40)

        self.input_step = TextInput(hint_text='Шаг измерений',
                                      multiline=False,font_size = 22,
                                      pos_hint={'center_x': 0.5, 'center_y': .5},
                                      size_hint=(1, None), height=40)

        self.btnCreate = Button(text='Создать',
                             size_hint=(1, None), height=40,font_size = 22,
                             pos_hint={'center_x': .5, 'center_y': .5},
                             color=(0, 47.5, 76.1, 1),
                             background_color=(255, 255, 255, 1))

        self.object = Label(text=' ',
                           color=(0,47.5,76.1,1),font_size = 22,
                           size_hint=(1, None), height=40,
                            pos_hint={'center_x': .5, 'center_y': .5})

        #self.input_object.bind(text=self.on_text)  # Добавляем обработчик события
        self.btnBT.bind(on_press=self.on_press_btnBT)
        self.btnCreate.bind(on_press=self.on_press_btnCreate)


    def on_press_btnBT(self, instance):
        print('BT')
    #system = glue.connect({...})
    def on_press_btnCreate(self, instance):

        Object = self.input_object.text
        Start = self.input_start.text
        Step = self.input_step.text

        if Start.isnumeric() and Step.isnumeric() and self.input_object.text > '':
            print('числа')
            self.input_start.text = str(float(Start))
            Start = str(float(self.input_start.text))
            self.input_step.text = str(float(Step))
            Step = self.input_step.text
            self.object.text = Object + ' ' + Start + 'км с шагом ' + Step + 'м'
            print('Create ' + ' ' + Object + ' ' + Start + ' ' + Step)

            df = pd.DataFrame({'km':[Start],
                               'pot':[Step]})
            df.to_excel(Object+'.xls')


            #my_file = open(Object+".xls", "a")
            #my_file.write(Start+","+Step+"\n")
            #my_file.close()


        elif Start.isnumeric()==False:
            self.input_start.text = ''
            self.input_start.hint_text=('Нужно ввести число')
            self.object.text = 'Начало измерений должно быть числом'
            self.input_start.bind(focus=on_focus)
            print('не число')
        elif Step.isnumeric()==False:
            self.input_step.text = ''
            self.input_step.hint_text=('Нужно ввести число')
            self.object.text = 'Шаг должен быть числом'
            self.input_step.bind(focus=on_focus)
            print('не число')
        elif self.input_object.text == '':
            print('введите название объекта')
            self.input_object.hint_text = ('Введите название объекта')
            self.object.text = 'Поле объект должно быть заполнено'
            self.input_object.bind(focus=on_focus)




    # Основной метод для построения программы
    def build(self):
        # Все объекты будем помещать в один общий слой
        Superbox = BoxLayout(orientation='vertical', padding=10, size_hint=(1, 0.5),pos_hint={'top': 1})
        Vbox = BoxLayout(orientation='vertical', padding=10)
        Vbox.add_widget(self.btnBT)
        Vbox.add_widget(self.input_object)

        H2box = BoxLayout(orientation='horizontal', padding=10, spacing = 10)
        H2box.add_widget(self.input_start)
        H2box.add_widget(self.input_step)

        Tbox = BoxLayout(orientation='vertical', padding=10)
        Tbox.add_widget(self.btnCreate)
        Tbox.add_widget(self.object)

        Superbox.add_widget(Vbox)
        Superbox.add_widget(H2box)
        Superbox.add_widget(Tbox)
        return Superbox

# Запуск проекта
if __name__ == "__main__":
    MyApp().run()